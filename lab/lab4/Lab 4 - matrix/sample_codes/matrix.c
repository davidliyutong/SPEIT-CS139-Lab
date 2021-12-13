#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

matrix_t* matrix_init(size_t dim[2]) {
    matrix_t* p_matrix = (matrix_t*)calloc(1, sizeof(matrix_t));
    if (p_matrix == NULL) {
        exit(FAIL_RETCODE);
    }

    p_matrix->arr = (double*)calloc(dim[0] * dim[1], sizeof(double));
    if (p_matrix->arr == NULL) {
        exit(FAIL_RETCODE);
    }

    memcpy(p_matrix->dim, dim, sizeof(size_t) * 2);

    return p_matrix;
}

err_t matrix_free(matrix_t* mat) {
    free(mat->arr);
    mat->arr = NULL;
    free(mat);
    return MATRIX_OK;
}

err_t matrix_repr(matrix_t* mat) {
    printf("array([");

    int row = 0, col = 0;
    for (row = 0; row < mat->dim[0]; ++row) {
        printf("[");
        for (col = 0; col < mat->dim[1]; ++col) {
            printf("%.3f, ", mat->arr[row * mat->dim[1] + col]);
        }
        if (row < mat->dim[0] - 1) {
            printf("\b\b],\n       ");
        } else {
            printf("\b\b]])\n\n");
        }
    }
    return MATRIX_OK;
}


err_t matrix_get_item(matrix_t* mat, size_t coord[2], double* val) {
    if (coord[0] < mat->dim[0] && coord[1] < mat->dim[1]) {
        *val = mat->arr[coord[0] * mat->dim[1] + coord[1]];
        return MATRIX_OK;
    } else {
        return MATRIX_FAIL;
    }
}

err_t matrix_set_item(matrix_t* mat, size_t coord[2], double val) {
    if (coord[0] < mat->dim[0] && coord[1] < mat->dim[1]) {
        mat->arr[coord[0] * mat->dim[1] + coord[1]] = val;
        return MATRIX_OK;
    } else {
        return MATRIX_FAIL;
    }
}

matrix_t* matrix_add(matrix_t* mat1, matrix_t* mat2, double lmd1, double lmd2, double k) {
    if (mat1->dim[0] != mat2->dim[0] || mat1->dim[1] != mat2->dim[1]) {
        return NULL;
    }

    matrix_t* res = matrix_init(mat1->dim);
    if (res == NULL) return NULL;

    size_t coord[2] = { 0 };
    double val1 = 0., val2 = 0.;
    for (coord[0] = 0; coord[0] < mat1->dim[0]; ++coord[0]) {
        for (coord[1] = 0; coord[1] < mat2->dim[1]; ++coord[1]) {
            matrix_get_item(mat1, coord, &val1);
            matrix_get_item(mat2, coord, &val2);
            matrix_set_item(res, coord, val1 * lmd1 + val2 * lmd2 + k);
        }
    }

    return res;

}

matrix_t* matrix_matmul(matrix_t* mat1, matrix_t* mat2) {
    if (mat1->dim[1] != mat2->dim[0]) {
        return NULL;
    }

    size_t dim[] = { mat1->dim[0], mat2->dim[1] };
    matrix_t* res = matrix_init(dim);
    if (res == NULL) return NULL;

    size_t res_coord[2] = { 0 };
    size_t mat1_coord[2] = { 0 };
    size_t mat2_coord[2] = { 0 };

    double val1 = 0., val2 = 0., sum = 0.;
    for (res_coord[0] = 0, mat1_coord[0] = 0; res_coord[0] < res->dim[0]; ++res_coord[0], ++mat1_coord[0]) {
        for (res_coord[1] = 0, mat2_coord[1] = 0; res_coord[1] < res->dim[1]; ++res_coord[1], ++mat2_coord[1]) {
            sum = 0.;
            for (int i = 0; i < mat1->dim[1]; ++i) {
                mat1_coord[1] = i;
                mat2_coord[0] = i;
                matrix_get_item(mat1, mat1_coord, &val1);
                matrix_get_item(mat2, mat2_coord, &val2);

                sum += val1 * val2;
            }
            matrix_set_item(res, res_coord, sum);
        }
    }

    return res;
}