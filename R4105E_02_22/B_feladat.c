#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>

void wait_one(void * args);
void kiir(int thread_id);

pthread_mutex_t value_mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    pthread_t threads[60];
    for (int i=0; i<60; i++)
        pthread_create(&threads[i], NULL, wait_one, i);
    for (int i=0; i<60; i++)
        pthread_join(threads[i], NULL);
    return 0;
}

void wait_one(void * args)
{
    Sleep(1000);
    kiir(args);
}

void kiir(int thread_id)
{
    pthread_mutex_lock(&value_mutex);
    printf("[thread %d] KESZ!\n", thread_id);
    pthread_mutex_unlock(&value_mutex);
}
