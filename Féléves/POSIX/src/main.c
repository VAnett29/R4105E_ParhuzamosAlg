#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "sod.h"
#include "thread_param.h"

#define NUM_THREADS 10
#define MAXNUMBER 10000
#define RANGE (MAXNUMBER / NUM_THREADS)

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
    FILE *f = fopen("c_threads.csv", "w"); //eredmények kiírása .csv fájlba diagramhoz
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    printf("\nResults:\n");
    fprintf(f, "Thread,Milliseconds,Numbers found\n"); // oszlop nevek
    for (int i = 0; i < NUM_THREADS; i++)
    {
        ThreadParam* data = &tParams[i];
        //console
        printf("[Thread %d] \t time: %10f millisecs, \t numbers found %4d\n", i, data->milliseconds, data->numbersFound);
        //csv fájl
        fprintf(f, "Thread %d,%f,%d\n", data->id, data->milliseconds, data->numbersFound);
    }

    printf ("\nFound %d numbers with sum of digits %d\n", result, sod);

    //felszabdítás
    fclose(f);
    pthread_mutex_destroy(&mutexsum);
    free(thr_ids);
    free(tParams);

    return EXIT_SUCCESS;
}
