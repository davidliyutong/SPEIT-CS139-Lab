#include <stdio.h>
int main() {
    int i = 0;

restart:
    printf("Hello, world\n");
    ++i;
    if (i < 10) goto restart;
    return 0;

}