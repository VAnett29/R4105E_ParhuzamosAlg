#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printRand(int lower, int upper, int count);

int main () {
 
    int lower=500, upper=1000, count =500;
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
