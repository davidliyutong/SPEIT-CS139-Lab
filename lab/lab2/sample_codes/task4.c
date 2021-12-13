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

int count_even(int* arr, int len) {
    /** 计算偶数的个数 **/
    /** 将cnt初始化为0 **/
    int cnt = 0;
    for (int i = 0; i < len; i++) {
        /** 遇到偶数就将cnt加一 **/
        if (arr[i] % 2 == 0) {
            ++cnt;
        }
    }
    return cnt;
}

int main(int argc, char** argv) {

    int arr[ARRAY_LEN];
    read_array(arr, ARRAY_LEN);
    display_array(arr, ARRAY_LEN);

    int cnt = 0;
    /** 计算偶数的个数 **/
    cnt = count_even(arr, ARRAY_LEN);
    printf("There are %d even numbers.\n", cnt);

    return 0;
}