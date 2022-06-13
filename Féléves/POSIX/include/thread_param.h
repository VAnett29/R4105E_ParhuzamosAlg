#ifndef THREAD_PARAM_H_INCLUDED
#define THREAD_PARAM_H_INCLUDED

#include <pthread.h>

int result; /* végeredmény */
pthread_mutex_t mutexsum; /* zároláshoz */

typedef struct ThreadParam /* adatok átadásához*/
{
    int id; // thread id
    int from; // tartomány eleje
    int to; //taromány vége
    int sumOfDigit; // szémjegyek össze amit kereseni kell
    int numbersFound; // Megtalált számok a megfelelő számjegy összeggel
    double milliseconds; // futási idő millisec-ben
} ThreadParam;

void init_tparam(ThreadParam* tParam, int id, int from, int to, int sod);

#endif // THREAD_PARAM_H_INCLUDED
