#ifndef MATRIX_TEST_CASES
#define MATRIX_TEST_CASES

#include <check.h>

#include "../s21_matrix.h"
#include "../s21_matrix_utils.h"
#include "test_utils.h"

TCase* s21_create_matrix_test_case();


TCase* s21_sum_matrix_test_case();
TCase* s21_sub_matrix_test_case();
TCase* s21_mult_number_test_case();
TCase* s21_mult_matrix_test_case();


TCase* s21_eq_matrix_test_case();


TCase* s21_transpose_test_case();
TCase* s21_calc_complements_test_case();
TCase* s21_determinant_test_case();
TCase* s21_inverse_matrix_test_case();

#endif
