#include "test_utils.h"

void s21_create_test_matrices(s21_matrix* A, s21_matrix* B, s21_matrix* result, s21_matrix* expected,
		int rows, int cols, double* array_A, double* array_B, double* array_expected)
{
	s21_create_matrix(rows, cols, A);
	s21_create_matrix(rows, cols, B);
	s21_create_matrix(rows, cols, result);
	s21_create_matrix(rows, cols, expected);

	s21_matrix_from_array(rows, cols, rows*cols, array_A, A);
	s21_matrix_from_array(rows, cols, rows*cols, array_B, B);
	s21_matrix_from_array(rows, cols, rows*cols, array_expected, expected);
}

void s21_remove_test_matrices(s21_matrix* A, s21_matrix* B, s21_matrix* result, s21_matrix* expected)
{
	s21_remove_matrix(A);
	s21_remove_matrix(B);
	s21_remove_matrix(result);
	s21_remove_matrix(expected);
}

