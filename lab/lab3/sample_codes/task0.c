#include <stdio.h>

int some_function(char * param1, int param2){
    printf("do %s for %d times\n", param1, param2);
    return -1;
};
int main(int argc, char ** argv) {
    int (*p)(char*, int);
    p = some_function;
    int ret = p("work", 996);
    printf(ret<0?"undingable":"dingable");
    return 0;
}