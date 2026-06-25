#include "s21_matrix.h"
#include "s21_matrix_utils.h"

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

	return MATRIX_OP_OK;
}

void s21_create_minor(int row, int col, s21_matrix* A, s21_matrix* minor)
{
	int minor_row = 0;
	int minor_col = 0;
	for (int i = 0; i < A->rows; i++)
	{
		for (int j = 0; j < A->columns; j++)
		{
			if (!(i == row || j == col))
			{
				minor->matrix[minor_row][minor_col++] = A->matrix[i][j];
			}
		}
		if (i != row) minor_row++;
		minor_col = 0;
	}

}

int s21_calc_complements(s21_matrix* A, s21_matrix* result)
{
	if (!A || !result || result->matrix == NULL || A->matrix == NULL) return MATRIX_OP_ERROR;
	if (A->rows != A->columns) return MATRIX_CALC_ERROR;

	int code = MATRIX_OP_OK;

	double det = 0;
	if (A->rows == 1)
	{
		code = s21_determinant(A, &det);
		if (!code) result->matrix[0][0] = det;
	}
	else 
	{
		for (int row = 0; row < result->rows; row++)
		{
			for (int col = 0; col < result->columns; col++)
			{
				s21_matrix lesser_matrix = {0};
				s21_create_matrix(A->rows - 1, A->columns - 1, &lesser_matrix);
				s21_create_minor(row, col, A, &lesser_matrix);
				s21_determinant(&lesser_matrix, &det);
				result->matrix[row][col] = pow(-1, (row + col)) * det;
				/*
				if (lesser_matrix->rows == 1)
				*/
				s21_remove_matrix(&lesser_matrix);
			}
		}
	}

	return code;
}

int s21_determinant(s21_matrix* A, double* result)
{
	if (!A || A->matrix == NULL) return MATRIX_OP_ERROR;
	if (A->rows != A->columns) return MATRIX_CALC_ERROR;

	int code = MATRIX_OP_OK;
	
	if (A->rows == 1) *result = A->matrix[0][0];
	else if (A->rows == 2) *result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
	else
	{
		s21_matrix complements = {0};
		s21_matrix complements_t = {0};
		s21_matrix determinants = {0};
		code += s21_create_matrix(A->rows, A->columns, &complements);
		code += s21_create_matrix(A->rows, A->columns, &complements_t);
		code += s21_create_matrix(A->rows, A->columns, &determinants);
		if (!code)
		{	
			code += s21_calc_complements(A, &complements);
			code += s21_transpose(&complements, &complements_t);
		}
		if (!code) code = s21_mult_matrix(A, &complements_t, &determinants);
		if (!code) *result = determinants.matrix[0][0];

		s21_remove_matrix(&complements);
		s21_remove_matrix(&complements_t);
		s21_remove_matrix(&determinants);
	}

	return code;
}

int s21_inverse_matrix(s21_matrix* A, s21_matrix* result)
{
	if (!A || !result) return MATRIX_OP_ERROR;
	if (A->matrix == NULL || result->matrix == NULL) return MATRIX_OP_ERROR;

	if (A->rows != A->columns) return MATRIX_CALC_ERROR;
	if (result->rows != A->rows || result->columns != A->columns) return MATRIX_CALC_ERROR;

	int code = MATRIX_OP_OK;

	double det = 0;
	code = s21_determinant(A, &det);

	if (det == 0) code = MATRIX_CALC_ERROR;
	else
	{
		s21_matrix complements = {0};
		s21_matrix complements_t = {0};
		code += s21_create_matrix(A->rows, A->columns, &complements);
		code += s21_create_matrix(A->rows, A->columns, &complements_t);
		
		if (!code) code = s21_calc_complements(A, &complements);
		if (!code) code = s21_transpose(&complements, &complements_t);

		if (!code) code = s21_mult_number(&complements_t, 1.0 / det, result);

		s21_remove_matrix(&complements);
		s21_remove_matrix(&complements_t);
	}

	return code;
}
