#ifndef S21_MATRIX_UTILS
#define S21_MATRIX_UTILS

#include <stdio.h>
#include "s21_matrix.h"

void s21_print_matrix(s21_matrix* matrix);

int s21_matrix_from_array(int rows, int cols, int array_size, double* array, s21_matrix* dest);

#endif
