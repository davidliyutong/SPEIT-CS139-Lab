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

void reverse_array(int* arr, int len) {
    /** 逆序 **/
    /** 将tmp用于交换元素 **/
    int tmp = 0;
    /** 记录前方下标 **/
    int head_idx = 0;
    /** 记录后方下标 **/
    int tail_idx = len - 1;
    while (head_idx < tail_idx) {
        /** 利用tmp交换变量 **/
        tmp = arr[head_idx];
        arr[head_idx] = arr[tail_idx];
        arr[tail_idx] = tmp;

        /** 分别改变下标的记录值 **/
        ++head_idx;
        --tail_idx;
    }
    printf("The array is reversed.\n");
}

int main(int argc, char** argv) {

    int arr[ARRAY_LEN];
    read_array(arr, ARRAY_LEN);
    display_array(arr, ARRAY_LEN);

    /** 逆序 **/
    reverse_array(arr, ARRAY_LEN);
    display_array(arr, ARRAY_LEN);

    return 0;
}