#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS 10
#define MAXNUMBER 10000
#define RANGE (MAXNUMBER / NUM_THREADS)

int result; /* végeredmény */
pthread_mutex_t mutexsum; /* zároláshoz */

typedef struct ThreadParam /* adatok átadásához*/
{
    int id; // thread id
    int from; // tartomány eleje
    int to; //tartomány vége
    int sumOfDigit; // számjegyek össze amit kereseni kell
} ThreadParam;

void* count_sum_of_digits(void*);

int sum_of_digit(int number);
void init_tparam(ThreadParam* tParam, int id, int from, int to, int sod);

int main (int argc, char **argv)
{
    ThreadParam* tParams; // paraméterek tömbje
    pthread_t* thr_ids; //szálak tömbje

    //tömb foglalások
    thr_ids = (pthread_t*) malloc(NUM_THREADS * sizeof(pthread_t));
    tParams = (ThreadParam*) malloc(NUM_THREADS * sizeof(ThreadParam));

    if (thr_ids == NULL || tParams == NULL) // memória foglalás ellenőrzése
    {
        exit (EXIT_FAILURE);
    }

    //szám bekérése
    printf("Enter a number: ");
    int number;
    scanf("%d", &number);

    // számjegyek összegének kiszámítása
    int sod = sum_of_digit(number);
    printf("Sum of digits for %d is %d\n", number, sod);

    //lock inicializálása
    pthread_mutex_init(&mutexsum, NULL);

    //paraméterek beállítása
    for (int i = 0; i < NUM_THREADS; i++)
    {
        init_tparam(&tParams[i], i, i * RANGE, (i + 1) * RANGE, sod);
    }

    //szálak létrehozása és indítása
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&thr_ids[i], NULL, count_sum_of_digits, &tParams[i]);
    }

    // szálak bevárása
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join (thr_ids[i], NULL);
    }

    //eredmény kiírása
    printf ("Found %d numbers with sum of digits %d\n", result, sod);

    //felszabdítás
    pthread_mutex_destroy(&mutexsum);
    free(thr_ids);
    free(tParams);

    return EXIT_SUCCESS;
}

//paraméterek beállítása
void init_tparam(ThreadParam* tParam, int id, int from, int to, int sod)
{
    tParam->id = id;
    tParam->from = from;
    tParam->to = to;
    tParam->sumOfDigit = sod;
}

//számjegyek összegének kiszámítása
int sum_of_digit(int number)
{
    int sumOfDigits = 0;
    while (number != 0) //ha a szám elfogyott kilépés
    {
        sumOfDigits += number % 10; //legkisebb helyiérték hozzáadása
        number /= 10; //legkisebb helyiérték eltüntetése
    }
    return sumOfDigits;
}

//szál függvény
void* count_sum_of_digits(void* arg)
{
    ThreadParam* data = (ThreadParam*) arg; //paraméter kasztolása adateléréshez
    printf("Thread %d starting from %d to %d finding %d\n", data->id, data->from, data->to, data->sumOfDigit);

    //végig futás a tartományon
    for(int i = data->from; i < data->to; i++)
    {
        if(sum_of_digit(i) == data->sumOfDigit) // ha egyezik a számjegyek összege
        {
            //kritikus szakaszban hozzáférés a közös globális változóhoz
            pthread_mutex_lock(&mutexsum);
            result += 1;
            pthread_mutex_unlock(&mutexsum);
        }
    }
    printf("Thread %d finished\n", data->id);
    // szál befejezése
    pthread_exit(EXIT_SUCCESS);
}
