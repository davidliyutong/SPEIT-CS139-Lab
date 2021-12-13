#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdint.h>
#include <stdlib.h>

#define FAIL_RETCODE (-1)
#define OK_RETCODE 0

enum err_t {
    MATRIX_OK,
    MATRIX_FAIL
};

typedef enum err_t err_t;

#define RANDINT(N) rand() % N
#define VALUE_MAX 8

err_t matrix_assign(double* mat, size_t n_row, size_t n_col);

err_t matrix_repr(double* mat, size_t n_row, size_t n_col);

err_t matrix_add(double* mat1,
                 double* mat2,
                 double* res,
                 double lmd1,
                 double lmd2,
                 double k,
                 size_t n_row, size_t n_col);

err_t matrix_matmul(double* mat1,
                    double* mat2,
                    double* res,
                    size_t n_row1, size_t n_col1,
                    size_t n_row2, size_t n_col2);
#endif