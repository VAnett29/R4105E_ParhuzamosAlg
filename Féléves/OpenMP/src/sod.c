#include "sod.h"

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
