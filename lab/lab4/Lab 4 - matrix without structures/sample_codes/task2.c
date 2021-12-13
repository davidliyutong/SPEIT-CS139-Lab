#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#define FAIL_RETCODE (-1)
#define OK_RETCODE 0

enum err_t {
    MATRIX_OK,
    MATRIX_FAIL
};

typedef enum err_t err_t;

#define RANDINT(N) rand() % N
#define VALUE_MAX 80

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


#define N_ROW 3
#define N_COL 3
int main(int argc, char** argv) {
    srand(time(NULL));

    double mat1[N_ROW][N_COL];
    matrix_assign((double*)mat1, N_ROW, N_COL);
    double mat2[N_ROW][N_COL];
    matrix_assign((double*)mat2, N_ROW, N_COL);

    double res[N_ROW][N_COL];
    matrix_add((double*)mat1, (double*)mat2, (double*)res, 1, 1, 0, N_ROW, N_COL);

    printf("\nmat1 = \n");
    matrix_repr((double*)mat1, N_ROW, N_COL);
    printf("\nmat2 = \n");
    matrix_repr((double*)mat2, N_ROW, N_COL);
    printf("\res = \n");
    matrix_repr((double*)res, N_ROW, N_COL);

    return 0;
}