#include "s21_matrix_utils.h"

int s21_matrix_from_array(int rows, int cols, int array_size, double* array, s21_matrix* dest)
{
	if (!rows || !cols || !array) return MATRIX_OP_ERROR;
	if (array_size != rows*cols) return MATRIX_OP_ERROR;

	int output = MATRIX_OP_OK;
	if (!dest || dest->matrix == NULL) output = s21_create_matrix(rows, cols, dest);

	if (output == MATRIX_OP_OK)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				dest->matrix[i][j] = array[i * cols + j];
			}
		}
	}
	
	return output;
}
