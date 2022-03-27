#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printRand(int lower, int upper, int count);

int main () {
 
    int lower=10000000, upper=99999999, count=1;
    srand(time(0));
    printRand(lower,upper,count);
   
   return(0);
}
void printRand(int lower, int upper, int count){
    int i;
    for(i=0; i<count; i++){
        int num = (rand()%(upper-lower+1))+lower;
        printf("%d\n", num);
    }
} 
