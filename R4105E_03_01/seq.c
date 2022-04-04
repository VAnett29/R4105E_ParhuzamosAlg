#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOF 10
float RNG_Double(float min, float max);

int main(int arc, char **argv)
{
    srand(time(NULL));
    float tomb[NOF];
    int i;
    float multiplicate = 1.0;

    for (i=0; i<NOF; i++)
        tomb[i] = RNG_Double(0.0,100.0); //0 és 100 között lebegőpontos szám generálás
    for (i=0; i<NOF; i++)
        multiplicate = multiplicate * tomb[i];
    printf("Az elemek osszeszorozva: %.2f\n", multiplicate);
}

float RNG_Double(float min, float max)
{
    float part = ((float)rand()) / RAND_MAX;
    float num = part * (max - min) + min;
    return num;
}
