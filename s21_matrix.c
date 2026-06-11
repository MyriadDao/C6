#include "s21_matrix.h"
#include <stdio.h>

static void s21_init_row(int row, int columns, s21_matrix* result)
{
	for (int i = 0; i < columns; i++)
	{
		result->matrix[row][i] = 0.0;
	}
}

int s21_create_matrix(int rows, int columns, s21_matrix* result)
{
	if (rows <= 0 || columns <= 0 || !result) 
	{
		return MATRIX_OP_ERROR;
	}
	int output = MATRIX_OP_OK;

	result->rows = rows;
	result->columns = columns;
	result->matrix = calloc(rows, sizeof(double*));
	if (result->matrix != NULL) 
	{
		for (int i = 0; i < rows; i++)
		{
			result->matrix[i] = calloc(columns, sizeof(double));
			if (result->matrix[i] != NULL) s21_init_row(i, columns, result);
			else 
			{
				output = MATRIX_OP_ERROR;
				break;
			}
		}
	}
	else output = MATRIX_OP_ERROR;

	return output;
}

int s21_remove_matrix(s21_matrix* matrix)
{
	if (!matrix || matrix->matrix == NULL) return MATRIX_OP_ERROR;
	int output = MATRIX_OP_OK;

	for (int i = 0; i < matrix->rows; i++)
	{
		if (matrix->matrix[i]) free(matrix->matrix[i]);
		else output = MATRIX_OP_ERROR;
	}
	free(matrix->matrix);

	return output;
}
