#include "sod.h"

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
