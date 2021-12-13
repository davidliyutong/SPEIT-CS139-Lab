#include <stdio.h>
#include "matrix.h"

int main(int argc, char** argv) {

    size_t dim[] = {5,5};
    matrix_t * pMat = matrix_init(dim);

    printf("\nmat = \n");
    matrix_repr(pMat);
    matrix_free(pMat);

    return 0;
}