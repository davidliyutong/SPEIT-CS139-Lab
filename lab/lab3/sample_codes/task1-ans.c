#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef void (* my_cb_typedef)(char*, int);

void some_process(my_cb_typedef callback) {
    /** 
     * time 函数可以获取当前时间 (time.h)
     * getpid 函数可以获取当前进程的进程号 (unistd.h)
    **/

    srand((unsigned int)time(NULL) * getpid());
    int random_number = rand();
    if (random_number < 1000000000) {
        return;
    } else {
        callback("random", random_number);
    }
}

/** 开始 - 可修改**/
void print_error(char * str, int num) {
    printf("Encountered error: %s. Number: %d\n", str, num);
}
/** 结束 - 可修改 **/

int main(int argc, char ** argv) {
    my_cb_typedef my_call_back_function;
    /** 开始 - 可修改**/
    my_call_back_function = print_error;
    /** 结束 - 可修改 **/

    some_process(my_call_back_function);
    return 0;
}