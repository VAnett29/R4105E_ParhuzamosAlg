#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int checkPrimeNumber(int n);
int main() {

  int n1, n2, i, flag;
  clock_t begin = clock();

  printf("Enter two positive integers: ");
  scanf("%d %d", &n1, &n2);

  if (n1 > n2) {
    n1 = n1 + n2;
    n2 = n1 - n2;
    n1 = n1 - n2;
  }

  printf("Prime numbers between %d and %d are: \n", n1, n2);
  for (i = n1 + 1; i < n2; ++i) {

    flag = checkPrimeNumber(i);

    if (flag == 1)
      printf("%d \n", i);
    }
    clock_t end = clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("\nThinking time: %f\n",time_spent);

    return 0;
  }

int checkPrimeNumber(int n) {
  int j, flag = 1;

  for (j = 2; j <= n / 2; ++j) {

    if (n % j == 0) {
      flag = 0;
      break;
    }
  }

  return flag;
}
