#include "s21_matrix.h"

int s21_transpose(s21_matrix* A, s21_matrix* result)
{
	if (!A || !result) return MATRIX_OP_ERROR;
	if (A->matrix == NULL || result->matrix == NULL) return MATRIX_OP_ERROR;
	if (A->rows != result->columns || A->columns != result->rows) return MATRIX_CALC_ERROR;

	for (int row = 0; row < A->rows; row++)
	{
		for (int col = 0; col < A->columns; col++)
		{
			result->matrix[col][row] = A->matrix[row][col];
		}
	}

	return MATRIX_OP_ERROR;
}

int s21_calc_complements(s21_matrix* A, s21_matrix* result)
{
	return MATRIX_OP_ERROR;
}

int s21_determinant(s21_matrix* A, double* result)
{
	return MATRIX_OP_ERROR;
}

int s21_inverse_matrix(s21_matrix* A, s21_matrix* result)
{
	return MATRIX_OP_ERROR;
}
