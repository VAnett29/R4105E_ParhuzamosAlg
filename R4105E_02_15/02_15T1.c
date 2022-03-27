#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sumofarray(const int arr[], int n);
int maxofarray(const int arr[], int n);
int minofarray(const int arr[], int n);

int main() {
    int arr[5] = {1,2,3,4,5};
    clock_t tic = clock();
    printf("Sum of array is %d\n", sumofarray(arr, sizeof(arr)/sizeof(int)));
    printf("Max of array is %d\n", maxofarray(arr, sizeof(arr)/sizeof(int)));
    printf("Min of array is %d\n", minofarray(arr, sizeof(arr)/sizeof(int)));
    clock_t toc = clock();
    double time_spent = (double)(toc - tic) / CLOCKS_PER_SEC;
    printf("CPU time spent: %f\n", time_spent);
    printf("\n");

    int randArr[5];
    srand(time(NULL));
    for (int i = 0; i < 5; i++) {
        randArr[i] = rand() % 6;
    }

    return 0;
}
int sumofarray(const int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int minofarray(const int arr[], int n) {
    int min = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int maxofarray(const int arr[], int n) {
    int max = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
