#ifndef TEST_UTILS
#define TEST_UTILS

#include "test_cases.h"

void s21_create_test_matrices(s21_matrix* A, s21_matrix* B, s21_matrix* result, s21_matrix* expected,
		int rows, int cols, double* array_A, double* array_B, double* array_expected);

void s21_remove_test_matrices(s21_matrix* A, s21_matrix* B, s21_matrix* result, s21_matrix* expected);

#endif
