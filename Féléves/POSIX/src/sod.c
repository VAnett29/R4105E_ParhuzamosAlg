#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "sod.h"
#include "thread_param.h"

//sz�l f�ggv�ny
void* count_sum_of_digits(void* arg)
{
    ThreadParam* data = (ThreadParam*) arg; //param�ter kasztol�sa adatel�r�shez
    printf("Thread %d starting from %d to %d finding %d\n", data->id, data->from, data->to, data->sumOfDigit);

    clock_t begin = clock();

    //v�gig fut�s a tartom�nyon
    for(int i = data->from; i < data->to; i++)
    {
        if(sum_of_digit(i) == data->sumOfDigit) // ha egyezik a sz�mjegyek �sszege
        {
            //kritikus szakaszban hozz�f�r�s a k�z�s glob�lis v�ltoz�hoz
            pthread_mutex_lock(&mutexsum);
            result += 1;
            pthread_mutex_unlock(&mutexsum);
            // tal�lat ki�r�sa
            data->numbersFound++;
            printf("[Thread %d] found %d\n", data->id, i);
        }
    }

    clock_t end = clock();
    data->milliseconds = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Thread %d finished under %f and found %d\n", data->id, data->milliseconds, data->numbersFound);
    // sz�l befejez�se
    pthread_exit(EXIT_SUCCESS);
}

//sz�mjegyek �sszeg�nek kisz�m�t�sa
int sum_of_digit(int number)
{
    int sumOfDigits = 0;
    while (number != 0) //ha a sz�m elfogyott kil�p�s
    {
        sumOfDigits += number % 10; //legkisebb helyi�rt�k hozz�ad�sa
        number /= 10; //legkisebb helyi�rt�k elt�ntet�se
    }
    return sumOfDigits;
}
