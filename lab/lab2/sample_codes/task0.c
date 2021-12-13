#include <stdio.h>

#define ARRAY_LEN 10

int main(int argc, char** argv) {

    int arr[ARRAY_LEN];

    printf("Enter the elements into the array: ");
    for (int i = 0; i < ARRAY_LEN; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nThe elements of the array are: ");
    for (int i = 0; i < ARRAY_LEN; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}