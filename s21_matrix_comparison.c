#include "s21_matrix.h"
#include <stdio.h>

static int s21_compare_double(double a, double b)
{
	int result = 1;
	if (fabs(a - b) < EPSILON) result = 0;

	return result;
}

int s21_eq_matrix(s21_matrix* A, s21_matrix* B)
{
	if (!A || !B) return MATRIX_OP_ERROR;
	if (A->matrix == NULL || B->matrix == NULL) return MATRIX_OP_ERROR;
	if ((A->rows != B->rows) || (A->columns != B->columns)) return MATRIX_CALC_ERROR;

	int result = EQ;

	for (int i = 0; i < A->rows; i++)
	{
		for (int j = 0; j < A->columns; j++)
		{
			if (s21_compare_double(A->matrix[i][j], B->matrix[i][j])) result = N_EQ;

		}
	}

	return result;
}
