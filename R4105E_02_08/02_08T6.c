#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int numb1= rand(), numb2 = rand();
    int amount;
    int answer;

    amount=numb1 + numb2;

    clock_t begin = clock();

    printf("%d + %d =?\t%d \n", numb1, numb2, amount);
  
    do{
        printf("Enter a number:");
        scanf("%d", &answer);

    }while(answer!=amount);
    clock_t end = clock();

    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Thining time: %f\n",time_spent);

    return 0;
}
