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

void array_max(int* arr, int len) {
    /** 求最大 **/
    /** res 初始化为arr[0] **/
    int res = arr[0];

    /** 如果找到更大的，将res修改成找到的值 **/
    for (int i = 0; i < len; i++) {
        if (arr[i] > res) {
            res = arr[i];
        }
    }
    /** 输出一串提示词和找到的最大值 **/
    printf("The maximum element of the array is: %d at index ", res);
    /** 将所有等于res的值的下标输出 **/
    for (int i = 0; i < len; i++) {
        if (arr[i] == res) {
            printf("%d, ", i);
        }
    }
    printf("\n");
}

void array_min(int* arr, int len) {
    /** 求最大，同上 **/
    int res = arr[0];
    for (int i = 0; i < len; i++) {
        if (arr[i] < res) {
            res = arr[i];
        }
    }
    printf("The maximum element of the array is: %d at index ", res);
    for (int i = 0; i < len; i++) {
        if (arr[i] == res) {
            printf("%d, ", i);
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {

    int arr[ARRAY_LEN];
    read_array(arr, ARRAY_LEN);
    display_array(arr, ARRAY_LEN);

    /** 求最大 **/
    array_max(arr, ARRAY_LEN);
    /** 求最小 **/
    array_min(arr, ARRAY_LEN);

    return 0;
}