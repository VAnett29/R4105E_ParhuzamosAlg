#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>
#include <stdio.h>

struct prime_t{
    int min, max, thread_id;
} typedef prime_t;

void * find_prime(void * args);
void kiir(int nr, int thread_id, int min, int max);
pthread_mutex_t value_mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    pthread_t threads[10];
    prime_t limit[10];
    limit[0].min = 1;
    limit[0].max = 99;
    limit[0].thread_id = 0;
    for (int i=0; i<10; i++)
    {
        pthread_create(&threads[i], NULL, find_prime, &limit[i]);
        limit[i+1].min = limit[i].max;
        limit[i+1].max = limit[i].max+100;
        limit[i].thread_id = i;
    }
    for (int i=0; i<10; i++)
    {
        pthread_join(threads[i],NULL);
    }
    return 0;
}

void * find_prime(void * args)
{
    prime_t* limit = args;
    int flag_var;
    int min = limit->min;
    int max = limit->max;
    int thread_id = limit->thread_id;
    int nr = 0; //A prímek száma
    for(int i=min+1; i<max; ++i)
    {
        flag_var=0;
        for(int j=2; j<=i/2; ++j)
        {
            if(i%j==0)
            {
                flag_var=1;
                break;
            }
        }
        if(flag_var==0)
            nr++;
    }
    kiir(nr, thread_id, min, max);
}

void kiir(int nr, int thread_id, int min, int max)
{
    pthread_mutex_lock(&value_mutex);
    printf("[thread %d] %d darab primet talaltam! (%d - %d)\n", thread_id, nr, min, max);
    pthread_mutex_unlock(&value_mutex);
}
