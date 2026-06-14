#ifndef S21_MATRIX
#define S21_MATRIX

#include <stdlib.h>
#include <math.h>

#define MATRIX_OP_OK 0
#define MATRIX_OP_ERROR 1
#define MATRIX_CALC_ERROR 2

#define EPSILON 1e-6

typedef struct matrix_struct
{
	double** matrix;
	int rows;
	int columns;
} s21_matrix;

int s21_create_matrix(int rows, int columns, s21_matrix* result);
int s21_remove_matrix(s21_matrix* matrix);


#define EQ 1
#define N_EQ 0 
int s21_eq_matrix(s21_matrix* A, s21_matrix* B);


int s21_sum_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result);
int s21_sub_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result);

int s21_mult_number(s21_matrix* A, double number, s21_matrix* result);
int s21_mult_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result); 


int s21_transpose(s21_matrix* A, s21_matrix* result);
int s21_calc_complements(s21_matrix* A, s21_matrix* result);
int s21_determinant(s21_matrix* A, double* result);
int s21_inverse_matrix(s21_matrix* A, s21_matrix* result);

#endif
