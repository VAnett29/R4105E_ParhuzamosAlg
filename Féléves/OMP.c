#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define MAXNUMBER 10000

int result;

int sum_of_digit(int number);

int main (int argc, char **argv)
{
    // szám bekérése
    printf("Enter a number: ");
    int number;
    scanf ("%d",&number);
    // számjegyek összegének kiszámítása
    int sod = sum_of_digit(number);
    printf("Sum of digits for %d is %d\n", number, sod);

    // lock inicializálása
    omp_lock_t lock;
    omp_init_lock(&lock);

    // OMP pragma használata a párhuzamos szakasz kijelöléséhez
    // automatikusan felosztja a for ciklus tartományát
    #pragma omp parallel
    #pragma omp for
    for(int i = 0; i < MAXNUMBER; i++)
    {
        if(sum_of_digit(i) == sod) // ha egyezik a számjegyek összeg
        {
            //kritikus szakasz a globális változó növeléséhez
            omp_set_lock(&lock);
            result += 1;
            omp_unset_lock(&lock);

            printf("[%d/%d] Found number %d with sum of digits %d\n", omp_get_thread_num(), omp_get_num_threads(), i, sod);
        }
    }
    // eredmény kiírása
    printf("Found %d numbers with sum of digits %d\n", result, sod);
    // felszabadítás
    omp_destroy_lock(&lock);

    return EXIT_SUCCESS;
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
