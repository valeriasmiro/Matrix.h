#include "s21_matrix.h"
#include "check.h"


START_TEST(s21_eq_matrix_1) {
    matrix_t A;
    matrix_t B;

    s21_create_matrix(1, 3, &A);
    s21_create_matrix(3, 1, &B);

    ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST


START_TEST(s21_eq_matrix_2) {
    matrix_t A;
    matrix_t B;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.columns; j++) {
            A.matrix[i][j] = i * A.columns + j + 1;
        }
    }

    for (int i = 0; i < B.rows; i++) {
        for (int j = 0; j < B.columns; j++) {
            B.matrix[i][j] = B.rows * B.columns - i * B.columns - j;
        }
    }

    ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST


START_TEST(s21_eq_matrix_3) {
    matrix_t A;
    matrix_t B;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.columns; j++) {
            A.matrix[i][j] = i * A.columns + j + 1;
            B.matrix[i][j] = i * B.columns + j + 1;
        }
    }

    ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST


START_TEST(s21_eq_matrix_4) {
    matrix_t A;
    matrix_t B;

    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);

    A.matrix[0][0] = 0.0000001;
    B.matrix[0][0] = 0.0000002;

    ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST


START_TEST(s21_sum_matrix_1) {
    matrix_t A;
    matrix_t B;
    matrix_t C;
    matrix_t result;

    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    s21_create_matrix(2, 2, &C);

    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;

    B.matrix[0][0] = 5;
    B.matrix[0][1] = 6;
    B.matrix[1][0] = 7;
    B.matrix[1][1] = 8;

    C.matrix[0][0] = 6;
    C.matrix[0][1] = 8;
    C.matrix[1][0] = 10;
    C.matrix[1][1] = 12;

    s21_sum_matrix(&A, &B, &result);

    ck_assert_int_eq(s21_eq_matrix(&C, &result), 1);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&C);
}
END_TEST


START_TEST(s21_sum_matrix_2) {
    matrix_t A;
    matrix_t B;
    matrix_t result;

    s21_create_matrix(1, 0, &A);
    s21_create_matrix(1, 1, &B);

    ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 1);

    s21_remove_matrix(&B);
}
END_TEST


START_TEST(s21_sum_matrix_3) {
    matrix_t A;
    matrix_t B;
    matrix_t result;

    s21_create_matrix(1, 2, &A);
    s21_create_matrix(2, 2, &B);

    for (int i = 0; i < A.rows; i++) {
      for (int j = 0; j < A.columns; j++) {
         A.matrix[i][j] = i * A.columns + j;
      }
    }

    for (int i = 0; i < B.rows; i++) {
      for (int j = 0; j < B.columns; j++) {
         B.matrix[i][j] = i * B.columns + j;
      }
    }

    ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 2);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST


START_TEST(s21_sub_matrix_1) {
    matrix_t A;
    matrix_t B;
    matrix_t C;
    matrix_t result;

    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    s21_create_matrix(2, 2, &C);

    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;

    B.matrix[0][0] = 6;
    B.matrix[0][1] = 3;
    B.matrix[1][0] = 1;
    B.matrix[1][1] = 9;

    C.matrix[0][0] = -5;
    C.matrix[0][1] = -1;
    C.matrix[1][0] = 2;
    C.matrix[1][1] = -5;

    s21_sub_matrix(&A, &B, &result);

    ck_assert_int_eq(s21_eq_matrix(&result, &C), 1);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&C);
}
END_TEST


START_TEST(s21_sub_matrix_2) {
    matrix_t A;
    matrix_t B;
    matrix_t result;

    s21_create_matrix(0, 0, &A);
    s21_create_matrix(0, 0, &B);


    ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 1);
}
END_TEST


START_TEST(s21_sub_matrix_3) {
    matrix_t A;
    matrix_t B;
    matrix_t result;

    s21_create_matrix(1, 2, &A);
    s21_create_matrix(2, 2, &B);

    for (int i = 0; i < A.rows; i++) {
      for (int j = 0; j < A.columns; j++) {
         A.matrix[i][j] = i * A.columns + j;
      }
    }

    for (int i = 0; i < B.rows; i++) {
      for (int j = 0; j < B.columns; j++) {
         B.matrix[i][j] = i * B.columns + j;
      }
    }

    ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 2);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST


START_TEST(s21_mult_number_1) {
    matrix_t A;
    matrix_t result;
    matrix_t C;

    s21_create_matrix(1, 3, &A);
    s21_create_matrix(1, 3, &C);

    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 4;

    double num = 5;

    C.matrix[0][0] = 5;
    C.matrix[0][1] = 10;
    C.matrix[0][2] = 20;

    s21_mult_number(&A, num, &result);

    ck_assert_int_eq(s21_eq_matrix(&result, &C), 1);

    s21_remove_matrix(&A);
    s21_remove_matrix(&C);
    s21_remove_matrix(&result);
}
END_TEST


START_TEST(s21_mult_number_2) {
    matrix_t A;
    matrix_t result;
    s21_create_matrix(0, 1, &A);
    double num = 1;

    ck_assert_int_eq(s21_mult_number(&A, num, &result), 1);
}
END_TEST


START_TEST(s21_mult_matrix_1) {
    matrix_t A;
    matrix_t B;
    matrix_t C;
    matrix_t result;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    s21_create_matrix(3, 3, &C);

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.columns; j++) {
            A.matrix[i][j] = i * A.columns + j;
            B.matrix[i][j] = A.columns * (A.rows - i) - j - 1;
        }
    }

    C.matrix[0][0] = 9;
    C.matrix[0][1] = 6;
    C.matrix[0][2] = 3;
    C.matrix[1][0] = 54;
    C.matrix[1][1] = 42;
    C.matrix[1][2] = 30;
    C.matrix[2][0] = 99;
    C.matrix[2][1] = 78;
    C.matrix[2][2] = 57;

    s21_mult_matrix(&A, &B, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &C), 1);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
    s21_remove_matrix(&result);
}
END_TEST


START_TEST(s21_mult_matrix_2) {
    matrix_t A;
    matrix_t B;
    matrix_t C;
    matrix_t result;

    s21_create_matrix(2, 3, &A);
    s21_create_matrix(3, 2, &B);
    s21_create_matrix(2, 2, &C);


    A.matrix[0][0] = 0;
    A.matrix[0][1] = 1;
    A.matrix[0][2] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;
    A.matrix[1][2] = 5;

    B.matrix[0][0] = 5;
    B.matrix[0][1] = 4;
    B.matrix[1][0] = 3;
    B.matrix[1][1] = 2;
    B.matrix[2][0] = 1;
    B.matrix[2][1] = 0;

    C.matrix[0][0] = 5;
    C.matrix[0][1] = 2;
    C.matrix[1][0] = 32;
    C.matrix[1][1] = 20;

    s21_mult_matrix(&A, &B, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &C), 1);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
    s21_remove_matrix(&result);
}
END_TEST


START_TEST(s21_mult_matrix_3) {
    matrix_t A;
    matrix_t B;
    matrix_t result;

    s21_create_matrix(1, 2, &A);
    s21_create_matrix(1, 2, &B);

    A.matrix[0][0] = 1;
    A.matrix[0][1] = 1;
    B.matrix[0][0] = 1;
    B.matrix[0][1] = 1;

    ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), 2);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST


START_TEST(s21_mult_matrix_4) {
    matrix_t A;
    matrix_t B;
    matrix_t result;

    s21_create_matrix(-1, 2, &A);
    s21_create_matrix(1, 2, &B);

    ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), 1);

    s21_remove_matrix(&B);
}
END_TEST


START_TEST(s21_transpose_1) {
    matrix_t A;
    matrix_t B;
    matrix_t result;

    s21_create_matrix(2, 3, &A);
    s21_create_matrix(3, 2, &B);

    A.matrix[0][0] = 0;
    A.matrix[0][1] = 1;
    A.matrix[0][2] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;
    A.matrix[1][2] = 5;

    B.matrix[0][0] = 0;
    B.matrix[0][1] = 3;
    B.matrix[1][0] = 1;
    B.matrix[1][1] = 4;
    B.matrix[2][0] = 2;
    B.matrix[2][1] = 5;

    s21_transpose(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &B), 1);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST


START_TEST(s21_transpose_2) {
    matrix_t A;
    matrix_t result;

    s21_create_matrix(0, 3, &A);

    ck_assert_int_eq(s21_transpose(&A, &result), 1);
}
END_TEST

START_TEST(s21_determinant_1) {
    matrix_t A;
    double res;

    s21_create_matrix(2, 3, &A);

    A.matrix[0][0] = 0;
    A.matrix[0][1] = 1;
    A.matrix[0][2] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;
    A.matrix[1][2] = 5;

    ck_assert_int_eq(s21_determinant(&A, &res), 2);
    s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_determinant_2) {
    matrix_t A;
    double res;

    s21_create_matrix(3, 3, &A);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A.matrix[i][j] = i * 3 + j + 1;
        }
    }

    s21_determinant(&A, &res);
    ck_assert_int_eq(res, 0);

    s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_determinant_3) {
    matrix_t A;
    double res;

    s21_create_matrix(2, 2, &A);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            A.matrix[i][j] = i * 2 + j + 1;
        }
    }

    s21_determinant(&A, &res);
    ck_assert_int_eq(res, -2);

    s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_determinant_4) {
    matrix_t A;
    double res;

    s21_create_matrix(1, 1 , &A);

    A.matrix[0][0] = 4;

    s21_determinant(&A, &res);
    ck_assert_int_eq(res, 4);

    s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_determinant_5) {
    matrix_t A;
    double res;

    s21_create_matrix(0, 1, &A);

    ck_assert_int_eq(s21_determinant(&A, &res), 1);
}
END_TEST


START_TEST(s21_calc_complements_1) {
    matrix_t A;
    matrix_t B;
    matrix_t result;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);

    A.matrix[0][0] = 2;
    A.matrix[0][1] = 3;
    A.matrix[0][2] = 5;
    A.matrix[1][0] = 7;
    A.matrix[1][1] = 1;
    A.matrix[1][2] = 4;
    A.matrix[2][0] = 9;
    A.matrix[2][1] = 10;
    A.matrix[2][2] = 6;

    B.matrix[0][0] = -34;
    B.matrix[0][1] = -6;
    B.matrix[0][2] = 61;
    B.matrix[1][0] = 32;
    B.matrix[1][1] = -33;
    B.matrix[1][2] = 7;
    B.matrix[2][0] = 7;
    B.matrix[2][1] = 27;
    B.matrix[2][2] = -19;

    s21_calc_complements(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &B), 1);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST


START_TEST(s21_calc_complements_2) {
    matrix_t A;
    matrix_t result;

    s21_create_matrix(0, 0, &A);

    ck_assert_int_eq(s21_calc_complements(&A, &result), 1);
}
END_TEST


START_TEST(s21_calc_complements_3) {
    matrix_t A;
    matrix_t result;

    s21_create_matrix(2, 3, &A);

    ck_assert_int_eq(s21_calc_complements(&A, &result), 2);
    s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_calc_complements_4) {
    matrix_t A;
    matrix_t result;

    s21_create_matrix(1, 1, &A);

    A.matrix[0][0] = 2;

    ck_assert_int_eq(s21_calc_complements(&A, &result), 2);

    s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_inverse_matrix_1) {
    matrix_t A;
    matrix_t B;
    matrix_t result;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);

    A.matrix[0][0] = 1;
    A.matrix[0][1] = 3;
    A.matrix[0][2] = -5;
    A.matrix[1][0] = 0;
    A.matrix[1][1] = 1;
    A.matrix[1][2] = 2;
    A.matrix[2][0] = 0;
    A.matrix[2][1] = 0;
    A.matrix[2][2] = 1;

    B.matrix[0][0] = 1;
    B.matrix[0][1] = -3;
    B.matrix[0][2] = 11;
    B.matrix[1][0] = 0;
    B.matrix[1][1] = 1;
    B.matrix[1][2] = -2;
    B.matrix[2][0] = 0;
    B.matrix[2][1] = 0;
    B.matrix[2][2] = 1;

    s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &B), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST


START_TEST(s21_inverse_matrix_2) {
    matrix_t A;
    matrix_t B;
    matrix_t result;

    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);

    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;

    B.matrix[0][0] = -2;
    B.matrix[0][1] = 1;
    B.matrix[1][0] = 1.5;
    B.matrix[1][1] = -0.5;


    s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &B), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST


START_TEST(s21_inverse_matrix_3) {
    matrix_t A;
    matrix_t result;

    s21_create_matrix(-1, -1, &A);

    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 1);
}
END_TEST


START_TEST(s21_inverse_matrix_4) {
    matrix_t A;
    matrix_t result;

    s21_create_matrix(4, 2, &A);

    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 2);
    s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_inverse_matrix_5) {
    matrix_t A;
    matrix_t result;
    double matrix_deter = 0;

    s21_create_matrix(1, 1, &A);

    A.matrix[0][0] = 0;

    s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 2);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_6) {
    matrix_t A;
    matrix_t B;
    matrix_t result;

    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);

    A.matrix[0][0] = -100;

    B.matrix[0][0] = -0.01;

    s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &B), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST


START_TEST(s21_inverse_matrix_7) {
    matrix_t A;
    matrix_t B;
    matrix_t result;
    double del = 2910;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);

    A.matrix[0][0] = -5;
    A.matrix[0][1] = 10;
    A.matrix[0][2] = 20;
    A.matrix[1][0] = 2;
    A.matrix[1][1] = -7;
    A.matrix[1][2] = 18;
    A.matrix[2][0] = 9;
    A.matrix[2][1] = 0;
    A.matrix[2][2] = 2;

    B.matrix[0][0] = -(14.0 / del);
    B.matrix[0][1] = -20.0 / del;
    B.matrix[0][2] = 320.0 / del;
    B.matrix[1][0] = 158.0 / del;
    B.matrix[1][1] = -190.0 / del;
    B.matrix[1][2] = 130.0 / del;
    B.matrix[2][0] = 63.0 / del;
    B.matrix[2][1] = 90.0 / del;
    B.matrix[2][2] = 15.0 / del;

    s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &B), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST


int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    srunner_set_fork_status(sr, CK_NOFORK);
    int nf;
    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, s21_eq_matrix_1);
    tcase_add_test(tc1_1, s21_eq_matrix_2);
    tcase_add_test(tc1_1, s21_eq_matrix_3);
    tcase_add_test(tc1_1, s21_eq_matrix_4);
    tcase_add_test(tc1_1, s21_sum_matrix_1);
    tcase_add_test(tc1_1, s21_sum_matrix_2);
    tcase_add_test(tc1_1, s21_sum_matrix_3);
    tcase_add_test(tc1_1, s21_sub_matrix_1);
    tcase_add_test(tc1_1, s21_sub_matrix_2);
    tcase_add_test(tc1_1, s21_sub_matrix_3);
    tcase_add_test(tc1_1, s21_mult_number_1);
    tcase_add_test(tc1_1, s21_mult_number_2);
    tcase_add_test(tc1_1, s21_mult_matrix_1);
    tcase_add_test(tc1_1, s21_mult_matrix_2);
    tcase_add_test(tc1_1, s21_mult_matrix_3);
    tcase_add_test(tc1_1, s21_mult_matrix_4);
    tcase_add_test(tc1_1, s21_transpose_1);
    tcase_add_test(tc1_1, s21_transpose_2);
    tcase_add_test(tc1_1, s21_determinant_1);
    tcase_add_test(tc1_1, s21_determinant_2);
    tcase_add_test(tc1_1, s21_determinant_3);
    tcase_add_test(tc1_1, s21_determinant_4);
    tcase_add_test(tc1_1, s21_determinant_5);
    tcase_add_test(tc1_1, s21_calc_complements_1);
    tcase_add_test(tc1_1, s21_calc_complements_2);
    tcase_add_test(tc1_1, s21_calc_complements_3);
    tcase_add_test(tc1_1, s21_calc_complements_4);
    tcase_add_test(tc1_1, s21_inverse_matrix_1);
    tcase_add_test(tc1_1, s21_inverse_matrix_2);
    tcase_add_test(tc1_1, s21_inverse_matrix_3);
    tcase_add_test(tc1_1, s21_inverse_matrix_4);
    tcase_add_test(tc1_1, s21_inverse_matrix_5);
    tcase_add_test(tc1_1, s21_inverse_matrix_6);
    tcase_add_test(tc1_1, s21_inverse_matrix_7);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
