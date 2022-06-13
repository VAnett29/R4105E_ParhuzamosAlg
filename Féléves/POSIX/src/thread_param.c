#include "thread_param.h"

//paraméterek beállítása
void init_tparam(ThreadParam* tParam, int id, int from, int to, int sod)
{
    tParam->id = id;
    tParam->from = from;
    tParam->to = to;
    tParam->sumOfDigit = sod;
    tParam->numbersFound = 0;
}
