#include <stdio.h>

#define N_ROW 3
#define N_COL 3

typedef enum err_t {
    MATRIX_OK = 0,
    MATRIX_FAIL = -1,
} err_t;

#define CHECK_DIM(row, col) \
    if (row == 0 || col == 0) { \
        return MATRIX_FAIL; \
    }\

err_t matrix_assign_value(double* mat, size_t n_row, size_t n_col) {
    CHECK_DIM(n_row, n_col);

    for (size_t row = 0; row < n_row; ++row) {
        for (size_t col = 0; col < n_col; ++col) {
            mat[row * n_col + col] = rand();
        }
        printf("\n");
    }

    return MATRIX_OK;
}

// err_t matrix_repr(double mat[][N_COL], size_t n_row, size_t n_col) {
err_t matrix_repr(double* mat, size_t n_row, size_t n_col) {
    CHECK_DIM(n_row, n_row);
    /** 等价于
    if (n_row == 0 || n_row == 0) {
        return MATRIX_FAIL;
    }
    **/
    for (size_t row = 0; row < n_row; ++row) {
        for (size_t col = 0; col < n_col; ++col) {
            printf("%f,", mat[row * n_col + col]);
        }
        printf("\n");
    }

    return MATRIX_OK;
}


int main() {
    double mat1[N_ROW][N_COL];
    mat1[0][0] = 0;
    // matrix_assign_value((double *)mat1, N_ROW, N_COL);
    matrix_repr(mat1, N_ROW, N_COL);

    return 0;
}