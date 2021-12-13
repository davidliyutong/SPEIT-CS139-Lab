#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdint.h>
#include <stdlib.h>

#define FAIL_RETCODE (-1)
#define OK_RETCODE 0

typedef struct matrix_t {
    double* arr;
    size_t dim[2]; // row, col
} matrix_t;

typedef enum err_t {
    MATRIX_OK,
    MATRIX_FAIL
}err_t;

matrix_t* matrix_init(size_t dim[2]);

err_t matrix_free(matrix_t* mat);

err_t matrix_repr(matrix_t* mat);

err_t matrix_get_item(matrix_t* mat, size_t coord[2], double* val);

err_t matrix_set_item(matrix_t* mat, size_t coord[2], double val);

matrix_t* matrix_add(matrix_t* mat1, matrix_t* mat2, double lmd1, double lmd2, double k);
matrix_t* matrix_matmul(matrix_t* mat1, matrix_t* mat2);

#endif