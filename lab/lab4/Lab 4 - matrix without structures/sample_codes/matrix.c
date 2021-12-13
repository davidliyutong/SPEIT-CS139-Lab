#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

err_t matrix_assign(double* mat, size_t n_row, size_t n_col) {
    for (size_t idx = 0; idx < n_row * n_col; ++idx) {
        mat[idx] = RANDINT(VALUE_MAX);
    }
    return MATRIX_OK;
}

err_t matrix_repr(double* mat, size_t n_row, size_t n_col) {
    printf("array([");

    size_t row = 0, col = 0;
    for (row = 0; row < n_row; ++row) {
        printf("[");
        for (col = 0; col < n_col; ++col) {
            printf("%.3f, ", mat[row * n_col + col]);
        }
        if (row < n_row - 1) {
            printf("\b\b],\n       ");
        } else {
            printf("\b\b]])\n\n");
        }
    }
    return MATRIX_OK;
}


err_t matrix_add(double* mat1,
                 double* mat2,
                 double* res,
                 double lmd1,
                 double lmd2,
                 double k,
                 size_t n_row, size_t n_col) {

    for (size_t idx = 0; idx < n_row * n_col; ++idx) {
        res[idx] = mat1[idx] * lmd1 + mat2[idx] * lmd2 + k;
    }

    return MATRIX_OK;
}

err_t matrix_matmul(double* mat1,
                    double* mat2,
                    double* res,
                    size_t n_row1, size_t n_col1,
                    size_t n_row2, size_t n_col2) {


    /**
     *
     *                              n_col2
     *                           |         |
     *                           |         |
     *                   n_row2  |         |
     *                           |         |
     *                           |         |
     *           n_col1
     *         ---------
     *  
     *  n_row1 
     * 
     *         ---------
     * 
    **/

    if (n_col1 != n_row2) {
        return MATRIX_FAIL;
    }
    size_t row = 0, col = 0;
    for (row = 0; row < n_row1; ++row) {
        for (col = 0; col < n_col2; ++col) {
            double sum = 0.;
            for (size_t idx = 0; idx < n_col1; ++idx) {
                sum += mat1[row * n_col1 + idx] * mat2[idx * n_col2 + col];
            }
            res[row * n_col2 + col] = sum;
        }
    }
    return MATRIX_OK;

}
