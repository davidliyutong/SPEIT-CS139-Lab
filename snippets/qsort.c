#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#define ARRAY_LEN 100
#define VALUE_MAX 80 // 80 < 100 so there are duplicated elements
#define RANDINT(N) rand() % N
#define DISPLAY_WIDTH 8

void randomize_arr(int* arr, size_t num) {
    srand(time(NULL));
    for (int idx = 0; idx < num; ++idx) {
        arr[idx] = RANDINT(VALUE_MAX);
    }
}

void display_arr(int* arr, size_t num) //print the content of array
{
    printf("array([");
    int row = 0, col = 0;
    for (row = 0; row < num / DISPLAY_WIDTH; ++row) {
        for (col = 0; col < DISPLAY_WIDTH; ++col) {
            printf("%2d, ", arr[row * DISPLAY_WIDTH + col]);
        }
        if ((row * DISPLAY_WIDTH + col) < num) {
            printf("\n       ");
        }
    }
    row = num / DISPLAY_WIDTH - 1;
    while ((row * DISPLAY_WIDTH + col) < num) {
        printf("%2d, ", arr[row * DISPLAY_WIDTH + col++]);
    }
    printf("\b\b])\n\n");
}

void _quicksort(int* arr, int start, int end)  //divide the problem into two parts, combination of "quicksort" and "partition"
{
    int _start = start;
    int _end = end; //instend of i j I use _start and _end as two index

    if (_end > _start) {

        int pivot = arr[_start];   //let pivot equals to the first element of array
        while (_start < _end) {
            while (arr[_end] >= pivot && _start < _end) { _end--; }    //avoid the confilct of duplicated numbers
            if (_start < _end) {
                arr[_start++] = arr[_end];
            }
            while (arr[_start] <= pivot && _start < _end) { _start++; }    //avoid the confilct of duplicated numbers
            if (_start < _end) {
                arr[_end--] = arr[_start];
            }
        }
        arr[_start] = pivot;   //let the last element equals to pivot

        int index_of_pivot = _start; // just a indicator
        _quicksort(arr, start, index_of_pivot - 1);
        _quicksort(arr, index_of_pivot + 1, end);
    }
}

void quicksort(int* arr, size_t num) {
    _quicksort(arr, 0, num - 1);
}

int main(int argc, char** argv) {
    int arr[ARRAY_LEN] = { 0 };

    int m = 0;
    int n = 0;

    randomize_arr(arr, ARRAY_LEN);
    display_arr(arr, ARRAY_LEN);
    quicksort(arr, ARRAY_LEN);
    display_arr(arr, ARRAY_LEN);

    return 0;
}