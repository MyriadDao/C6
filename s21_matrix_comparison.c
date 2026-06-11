#include "s21_matrix.h"

static int s21_compare_double(double a, double b)
{
	int result = 1;
	if (fabs(a - b) < EPSILON) result = 0;

	return result;
}

int s21_eq_matrix(s21_matrix* A, s21_matrix* B)
{
	if (!A || !B) return MATRIX_OP_ERROR;

	int result = EQ;
	if ((A->rows != B->rows) || (A->columns != B->columns)) result = N_EQ;

	for (int i = 0; i < A->columns; i++)
	{
		for (int j = 0; j < A->rows; j++)
		{
			//if (A->matrix[i][j] != B->matrix[i][j]) result = N_EQ;
			if (s21_compare_double(A->matrix[i][j], B->matrix[i][j])) result = N_EQ;
		}
	}

	return result;
}
