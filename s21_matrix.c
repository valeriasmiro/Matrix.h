#include "s21_matrix.h"


int s21_create_matrix(int rows, int columns, matrix_t* result) {
    int func_res = 0;
    if (rows > 0 && columns > 0) {
        result->rows = rows;
        result->columns = columns;
        result->matrix = (double**)malloc(rows * sizeof(double*));
        for (int i = 0; i < rows; i++) {
            result->matrix[i] = (double*)malloc(columns * sizeof(double));
            for (int j = 0; j < columns; j++) {
            result->matrix[i][j] = 0.000000;
            }
        }
    } else {
        result->rows = 0;
        result->columns = 0;
        result->matrix = NULL;
        func_res = 1;
    }
    return func_res;
}


int is_matrix_correct(matrix_t* A) {
    int func_res =  SUCCESS;
    if (A->rows < 1 || A->columns < 1)
        func_res = FAILURE;
    return func_res;
}


void s21_remove_matrix(matrix_t* A) {
    for (int i = 0; i < A->rows; i++)
        free(A->matrix[i]);
    free(A->matrix);
    A->rows = 0;
    A->columns = 0;
}


int s21_eq_matrix(matrix_t* A, matrix_t* B) {
    int func_res = SUCCESS;
    if (are_sizes_same(A, B) && is_matrix_correct(A) && is_matrix_correct(B)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) {
                    func_res = FAILURE;
                }
            }
        }
    } else {
        func_res = FAILURE;
    }
    return func_res;
}


int are_sizes_same(matrix_t* A, matrix_t* B) {
    int func_res = SUCCESS;
    if (A->rows != B->rows || A->columns != B->columns)
        func_res = FAILURE;
    return func_res;
}


int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
    int func_res = 0;
    if (are_sizes_same(A, B) && is_matrix_correct(A) && is_matrix_correct(B)) {
        int rows = A->rows;
        int columns = A->columns;
        s21_create_matrix(rows, columns, result);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
    } else if (!is_matrix_correct(A) || !is_matrix_correct(B)) {
        func_res = 1;
    } else {
        func_res = 2;
    }
    return func_res;
}


int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
    int func_res = 0;
    if (are_sizes_same(A, B) && is_matrix_correct(A) && is_matrix_correct(B)) {
        int rows = A->rows;
        int columns = A->columns;
        s21_create_matrix(rows, columns, result);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
    } else if (!is_matrix_correct(A) || !is_matrix_correct(B)) {
        func_res = 1;
    } else {
        func_res = 2;
    }
    return func_res;
}


int s21_mult_number(matrix_t* A, double number, matrix_t* result) {
    int func_res = 0;
    if (is_matrix_correct(A)) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
    } else {
        func_res = 1;
    }
    return func_res;
}


int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
    int func_res = 0;
    int rows = A->rows;
    int columns = B->columns;
    double element = 0;
    if (is_matrix_correct(A) && is_matrix_correct(B) && A->columns == B->rows) {
        s21_create_matrix(rows, columns, result);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                element = 0;
                for (int k = 0; k < A->columns; k++) {
                    element += A->matrix[i][k] * B->matrix[k][j];
                }
                result->matrix[i][j] = element;
            }
        }
    } else if (!is_matrix_correct(A) || !is_matrix_correct(B)) {
        func_res = 1;
    } else {
        func_res = 2;
    }
    return func_res;
}


int s21_transpose(matrix_t* A, matrix_t* result) {
    int func_res = 0;
    if (is_matrix_correct(A)) {
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[j][i];
            }
         }
    } else {
        func_res = 1;
    }
    return func_res;
}


int find_minor_ij(matrix_t* A, int del_row, int del_column, double *minor_ij) {
    matrix_t matrix_for_minor;
    s21_create_matrix(A->rows - 1, A->columns - 1, &matrix_for_minor);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            if (i < del_row && j < del_column) {
                matrix_for_minor.matrix[i][j] = A->matrix[i][j];
            } else if (i < del_row && j > del_column) {
                matrix_for_minor.matrix[i][j - 1] = A->matrix[i][j];
            } else if (i > del_row && j < del_column) {
                matrix_for_minor.matrix[i - 1][j] = A->matrix[i][j];
            } else if (i > del_row && j > del_column) {
                matrix_for_minor.matrix[i - 1][j - 1] = A->matrix[i][j];
            }
        }
    }

    s21_determinant(&matrix_for_minor, minor_ij);
    s21_remove_matrix(&matrix_for_minor);
}


int s21_determinant(matrix_t* A, double* result) {
    int func_res = 0;
    double minor_ij = 0;

    if (A->rows == A->columns && A->rows > 0) {
        if (A->rows == 1) {
            *result = A->matrix[0][0];
        } else if (A->rows == 2) {
            *result += A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
        } else if (A->rows > 2) {
            for (int j = 0; j < A->columns; j++) {
                minor_ij = 0;
                find_minor_ij(A, 0, j, &minor_ij);

                *result += pow(-1, j) * A->matrix[0][j] * minor_ij;
            }
        }
    } else if (!is_matrix_correct(A)) {
        func_res = 1;
    } else {
        func_res = 2;
    }
    return func_res;
}


int s21_calc_complements(matrix_t* A, matrix_t* result) {
    int func_res = 0;

    if (A->rows == A->columns && A->rows > 1) {
        int n = A->rows;
        double minor_ij;

        s21_create_matrix(n, n, result);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                minor_ij = 0;
                find_minor_ij(A, i, j, &minor_ij);
                result->matrix[i][j] = minor_ij * pow(-1, i + j);
            }
        }
    } else if (!is_matrix_correct(A)) {
        func_res = 1;
    } else {
        func_res = 2;
    }
    return func_res;
}


int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int func_res = 0;
    double matrix_deter = 0;

    if (is_matrix_correct(A)) {
        int check = s21_determinant(A, &matrix_deter);
        if (check == 0 && matrix_deter) {
            if (A->rows == 1) {
                s21_create_matrix(1, 1, result);
                result->matrix[0][0] = (double) 1 / A->matrix[0][0];
            } else {
                int n = A->rows;
                double koef = (double) 1 / matrix_deter;
                matrix_t compl_matrix;
                matrix_t transposed_compl_matrix;

                s21_calc_complements(A, &compl_matrix);
                s21_transpose(&compl_matrix, &transposed_compl_matrix);
                s21_mult_number(&transposed_compl_matrix, koef, result);

                s21_remove_matrix(&compl_matrix);
                s21_remove_matrix(&transposed_compl_matrix);
            }
        } else {
            func_res = 2;
        }
    } else {
        func_res = 1;
    }
    return func_res;
}
