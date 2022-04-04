#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOF 10

float RNG_Double(float min, float max);
float recursive_multi(float * tomb, int size);

int main(int arc, char **argv)
{
    srand(time(NULL));
    float tomb[NOF];
    int i;

    for (i=0; i<NOF; i++)
        tomb[i] = RNG_Double(0.0,100.0); //0 és 100 között lebegőpontos szám generálás
    printf("Az elemek osszeszorozva: %.2f\n", recursive_multi(tomb, NOF));
}

float RNG_Double(float min, float max)
{
    float part = ((float)rand()) / RAND_MAX;
    float num = part * (max - min) + min;
    return num;
}

float recursive_multi(float * tomb, int size)
{
    float lhalf = 1;
    float rhalf = 1;
    if (size == 1){
        return tomb[0];
    }
    else
    {
        lhalf = recursive_multi(tomb, size/2);
        rhalf = recursive_multi(tomb+(size/2), size-(size/2));
        return lhalf*rhalf;
    }
}
