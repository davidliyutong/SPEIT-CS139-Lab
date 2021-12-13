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

int read_query() {
    /** 读取一个需要查找的数 **/
    int query = 0;
    printf("Input the number to query:\n>>> ");
    scanf("%d", &query);
    printf("\n");
    fflush(stdin);
    return query;
}

void search_array(int* arr, int len, int query) {
    /**将结果初始化为-1，一个不可能出现的值 **/
    int res = -1;
    /** 遍历数组进行搜索 **/
    for (int i = 0; i < len; i++) {
        if (arr[i] == query) {
            /** 如果第一次找到结果，打印一串提示 **/
            if (res < 0) {
                printf("The number exists, its index is %d", i);
            } else {
                printf(", %d", i);
            }
            /** 修改res，使其变成找到的下标 **/
            res = i;
        }
    }
    /** 如果没有找到结果，res == -1，打印一串提示 **/
    if (res < 0) {
        printf("The number does not exist.\n");
    } else {
        /** 如果找到结果，res > 0，打印一串提示 **/
        printf("\n");
    }
}

int main(int argc, char** argv) {

    int arr[ARRAY_LEN];
    read_array(arr, ARRAY_LEN);
    display_array(arr, ARRAY_LEN);

    int query = 0;
    /** 获取一个查询值 **/
    query = read_query();
    /** 进行查询 **/
    search_array(arr, ARRAY_LEN, query);

    return 0;
}