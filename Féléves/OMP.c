#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define MAXNUMBER 10000

int result;

int sum_of_digit(int number);

int main (int argc, char **argv)
{
    // sz�m bek�r�se
    printf("Enter a number: ");
    int number;
    scanf ("%d",&number);
    // sz�mjegyek �sszeg�nek kisz�m�t�sa
    int sod = sum_of_digit(number);
    printf("Sum of digits for %d is %d\n", number, sod);

    // lock inicializ�l�sa
    omp_lock_t lock;
    omp_init_lock(&lock);

    // OMP pragma haszn�lata a p�rhuzamos szakasz kijel�l�s�hez
    // automatikusan felosztja a for ciklus tartom�ny�t
    #pragma omp parallel
    #pragma omp for
    for(int i = 0; i < MAXNUMBER; i++)
    {
        if(sum_of_digit(i) == sod) // ha egyezik a sz�mjegyek �sszeg
        {
            //kritikus szakasz a glob�lis v�ltoz� n�vel�s�hez
            omp_set_lock(&lock);
            result += 1;
            omp_unset_lock(&lock);

            printf("[%d/%d] Found number %d with sum of digits %d\n", omp_get_thread_num(), omp_get_num_threads(), i, sod);
        }
    }
    // eredm�ny ki�r�sa
    printf("Found %d numbers with sum of digits %d\n", result, sod);
    // felszabad�t�s
    omp_destroy_lock(&lock);

    return EXIT_SUCCESS;
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
