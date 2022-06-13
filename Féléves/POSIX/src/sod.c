#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "sod.h"
#include "thread_param.h"

//szál függvény
void* count_sum_of_digits(void* arg)
{
    ThreadParam* data = (ThreadParam*) arg; //paraméter kasztolása adateléréshez
    printf("Thread %d starting from %d to %d finding %d\n", data->id, data->from, data->to, data->sumOfDigit);

    clock_t begin = clock();

    //végig futás a tartományon
    for(int i = data->from; i < data->to; i++)
    {
        if(sum_of_digit(i) == data->sumOfDigit) // ha egyezik a számjegyek összege
        {
            //kritikus szakaszban hozzáférés a közös globális változóhoz
            pthread_mutex_lock(&mutexsum);
            result += 1;
            pthread_mutex_unlock(&mutexsum);
            // találat kiírása
            data->numbersFound++;
            printf("[Thread %d] found %d\n", data->id, i);
        }
    }

    clock_t end = clock();
    data->milliseconds = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Thread %d finished under %f and found %d\n", data->id, data->milliseconds, data->numbersFound);
    // szál befejezése
    pthread_exit(EXIT_SUCCESS);
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
