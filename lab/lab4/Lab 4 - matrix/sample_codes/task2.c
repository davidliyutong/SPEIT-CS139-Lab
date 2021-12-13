#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define FAIL_RETCODE (-1)
#define OK_RETCODE 0

typedef struct matrix_t {
    double * arr;
    size_t dim[2]; // row, col
} matrix_t;

typedef enum err_t {
    MATRIX_OK,
    MATRIX_FAIL
}err_t;

matrix_t * matrix_init(size_t dim[2]) {
    matrix_t * p_matrix = (matrix_t *)calloc(1, sizeof(matrix_t));
    if (p_matrix == NULL) {
        exit(FAIL_RETCODE);
    }

    p_matrix->arr = (double *)calloc(dim[0] * dim[1], sizeof(double));
    if (p_matrix->arr == NULL) {
        exit(FAIL_RETCODE);
    }

    memcpy(p_matrix->dim, dim, sizeof(size_t) * 2);

    return p_matrix;
}

err_t matrix_free(matrix_t *mat) {
    free(mat->arr);
    mat->arr = NULL;
    free(mat);
    return MATRIX_OK;
}

err_t matrix_repr(matrix_t * mat) {
    printf("array([");

    int row = 0, col = 0;
    for (row = 0; row < mat->dim[0]; ++row) {
        printf("[");
        for (col = 0; col < mat->dim[1]; ++col) {
            printf("%.3f, ", mat->arr[row * mat->dim[1] + col]);
        }
        if (row < mat->dim[0] - 1) {
            printf("\b\b],\n       ");
        } else{
            printf("\b\b]])\n\n");
        }
    }
    return MATRIX_OK;
}


err_t matrix_get_item(matrix_t * mat, size_t coord[2], double * val) {
    if (coord[0] < mat->dim[0] && coord[1] < mat->dim[1]) {
        *val = mat->arr[coord[0] * mat->dim[1] + coord[1]];
        return MATRIX_OK;
    } else {
        return MATRIX_FAIL;
    }
}

err_t matrix_set_item(matrix_t * mat, size_t coord[2], double val) {
    if (coord[0] < mat->dim[0] && coord[1] < mat->dim[1]) {
        mat->arr[coord[0] * mat->dim[1] + coord[1]] = val;
        return MATRIX_OK;
    } else {
        return MATRIX_FAIL;
    }
}


int main(int argc, char** argv) {

    size_t dim[] = {5,5};
    matrix_t * pMat = matrix_init(dim);

    size_t coord[] = {1,1};
    matrix_set_item(pMat, coord, 5);
    
    printf("\nmat = \n");
    matrix_repr(pMat);
    matrix_free(pMat);

    return 0;
}