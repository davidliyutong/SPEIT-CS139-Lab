#include <stdio.h>
#include <stdlib.h>

void func() {
    char * a_piece_of_memory = (char *)malloc(10);
}

int main()
{
    func();
    return 0;
}