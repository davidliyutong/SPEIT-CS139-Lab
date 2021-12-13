#include <stdio.h>

#define ARRAY_LEN 10

void read_array(int* arr, int len) {
    int ret;
    printf("Enter the elements into the array: ");
    for (int i = 0; i < len; i++) {
        ret = scanf("%d", &arr[i]);
    }
    fflush(stdin);
    return;
}

void display_array(int* arr, int len) {
    printf("\nThe elements of the array are: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return;
}

long long int sum_array(int* arr, int len) {
    long long int sum = 0;
    /** 遍历求和 **/
    for (int i = 0; i < len; i++) {
        sum += arr[i];
    }
    return sum;
}

int main(int argc, char** argv) {

    int arr[ARRAY_LEN];
    read_array(arr, ARRAY_LEN);
    display_array(arr, ARRAY_LEN);

    long long int sum = 0;
    /** 求和 **/
    sum = sum_array(arr, ARRAY_LEN);
    printf("The sum of array is %lld.\n", sum);

    return 0;
}