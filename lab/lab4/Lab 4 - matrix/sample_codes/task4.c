#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char** argv) {

    size_t dim[] = { 5,5 };
    matrix_t* pMat1 = matrix_init(dim);
    matrix_t* pMat2 = matrix_init(dim);

    size_t coords1[] = { 0,0, 1,1, 2,2, 3,3 };
    for (size_t* coord = coords1; coord < coords1 + (sizeof(coords1) / (sizeof(size_t))); coord += 2) {
        matrix_set_item(pMat1, coord, 1);
    }

    size_t coords2[] = { 0,0, 0,1,0,2,0,3 };
    for (size_t* coord = coords2; coord < coords2 + (sizeof(coords2) / (sizeof(size_t))); coord += 2) {
        matrix_set_item(pMat2, coord, 10);
    }

    double k = -1.;
    double lmd1 = 2.;
    double lmd2 = 1.;

    matrix_t* pMat3 = matrix_add(pMat1, pMat2, lmd1, lmd2, k);
    matrix_t* pMat4 = matrix_matmul(pMat3, pMat2);


    printf("\nmat1 = \n");
    matrix_repr(pMat1);
    printf("\nmat2 = \n");
    matrix_repr(pMat2);
    printf("\nmat3 = \n");
    matrix_repr(pMat3);
    printf("\nmat4 = \n");
    matrix_repr(pMat4);

    matrix_free(pMat1);
    matrix_free(pMat2);
    matrix_free(pMat3);
    matrix_free(pMat4);


    return 0;
}