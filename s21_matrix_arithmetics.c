#include "s21_matrix.h"

int s21_sum_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result)
{
	if (!A || !B || !result) return MATRIX_OP_ERROR;

	for (int i = 0; i < result->columns; i++)
	{
		for (int j = 0; j < result->rows; j++)
		{

		}

	}

	return MATRIX_OP_ERROR;
}

int s21_sub_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result)
{
	return MATRIX_OP_ERROR;
}

int s21_mult_number(s21_matrix* A, double number, s21_matrix* result)
{
	return MATRIX_OP_ERROR;
}

int s21_mult_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result)
{
	return MATRIX_OP_ERROR;
}
