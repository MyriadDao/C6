#include "s21_matrix.h"

static int s21_check_matrices(s21_matrix* A, s21_matrix* B, s21_matrix* result)
{
	if (!A || !B || !result) return MATRIX_OP_ERROR;
	if (A->matrix == NULL || B->matrix == NULL || result->matrix == NULL) return MATRIX_OP_ERROR;
	if (A->rows != B->rows || A->columns != B->columns) return MATRIX_CALC_ERROR;
	if (A->rows != result->rows || A->columns != B->columns) return MATRIX_CALC_ERROR;

	return MATRIX_OP_OK;
}

int s21_sum_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result)
{
	int output = s21_check_matrices(A, B, result);
	if (output) return output;

	for (int i = 0; i < result->columns; i++)
	{
		for (int j = 0; j < result->rows; j++)
		{
			result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
		}

	}

	return output;
}

int s21_sub_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result)
{
	int output = s21_check_matrices(A, B, result);
	if (output) return output;

	for (int i = 0; i < result->columns; i++)
	{
		for (int j = 0; j < result->rows; j++)
		{
			result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
		}

	}

	return output;
}

int s21_mult_number(s21_matrix* A, double number, s21_matrix* result)
{
	return MATRIX_OP_ERROR;
}

int s21_mult_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result)
{
	return MATRIX_OP_ERROR;
}
