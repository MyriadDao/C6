#include "s21_matrix_utils.h"

void s21_print_matrix(s21_matrix* matrix)
{
	if (!matrix) return;

	for (int i = 0; i < matrix->rows; i++)
	{
		for (int j = 0; j < matrix->columns; j++)
		{
			printf("%lf ", matrix->matrix[i][j]);
		}
		printf("\n");
	}
}

int s21_matrix_from_array(int rows, int cols, int array_size, double* array, s21_matrix* dest)
{
	if (!rows || !cols || !array) return MATRIX_OP_ERROR;
	if (array_size != rows*cols) return MATRIX_OP_ERROR;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			dest->matrix[i][j] = array[i * rows + j];
		}
	}
	
	return MATRIX_OP_OK;
}
