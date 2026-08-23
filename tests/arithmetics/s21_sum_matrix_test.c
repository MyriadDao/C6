#include "../test_cases.h"

START_TEST(test_1)
{
	s21_matrix A;
	s21_matrix B;
	s21_matrix result;
	s21_matrix expected;

	double array1[4] = {1.0, 2.0, 3.0, 4.0};
	double array2[4] = {1.0, 2.0, 3.0, 4.0};
	double expected_array[4] = {2.0, 4.0, 6.0, 8.0};

	int rows = 2;
	int cols = 2;

	s21_create_test_matrices(&A, &B, &result, &expected,
			rows, cols, array1, array2, expected_array);

	s21_sum_matrix(&A, &B, &result);

	int code = s21_eq_matrix(&result, &expected);
	
	s21_remove_test_matrices(&A, &B, &result, &expected);

	ck_assert_int_eq(code, EQ);
}
END_TEST

START_TEST(test_2)
{
	s21_matrix A = {0};
	s21_matrix B = {0};
	s21_matrix result = {0};


	int code = s21_sum_matrix(&A, &B, &result);

	s21_remove_test_matrices(&A, &B, &result, NULL);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_3)
{
	s21_matrix A = {0};
	s21_matrix B;
	s21_matrix result;

	s21_create_matrix(1, 1, &result);
	s21_create_matrix(1, 1, &B);

	int code = s21_sum_matrix(&A, &B, &result);

	s21_remove_test_matrices(&A, &B, &result, NULL);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_4)
{
	s21_matrix A;
	s21_matrix B = {0};
	s21_matrix result;

	s21_create_matrix(1, 1, &A);
	s21_create_matrix(1, 1, &result);

	int code = s21_sum_matrix(&A, &B, &result);

	s21_remove_test_matrices(&A, &B, &result, NULL);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_5)
{
	s21_matrix A;
	s21_matrix B;
	s21_matrix result = {0};

	s21_create_matrix(1, 1, &A);
	s21_create_matrix(1, 1, &B);

	int code = s21_sum_matrix(&A, &B, &result);

	s21_remove_test_matrices(&A, &B, &result, NULL);

	ck_assert_int_eq(code, MATRIX_OP_OK);
}
END_TEST

START_TEST(test_6)
{
	s21_matrix A;
	s21_matrix B;
	s21_matrix result;

	int rows = 2;
	int cols = 2;

	s21_create_matrix(rows, 1, &A);
	s21_create_matrix(rows, cols, &B);
	s21_create_matrix(rows, cols, &result);

	int code = s21_sum_matrix(&A, &B, &result);
	
	s21_remove_test_matrices(&A, &B, &result, NULL);

	ck_assert_int_eq(code, MATRIX_CALC_ERROR);
}
END_TEST

START_TEST(test_7)
{
	s21_matrix A;
	s21_matrix B;
	s21_matrix result;

	int rows = 2;
	int cols = 2;

	s21_create_matrix(rows, cols, &A);
	s21_create_matrix(rows, 1, &B);
	s21_create_matrix(rows, cols, &result);

	int code = s21_sum_matrix(&A, &B, &result);
	
	s21_remove_test_matrices(&A, &B, &result, NULL);

	ck_assert_int_eq(code, MATRIX_CALC_ERROR);
}
END_TEST

START_TEST(test_8)
{
	s21_matrix A;
	s21_matrix B;
	s21_matrix result = {0};

	s21_create_matrix(2, 2, &A);
	s21_create_matrix(3, 3, &B); 

	int code = s21_sum_matrix(&A, &B, &result);
	
	s21_remove_test_matrices(&A, &B, &result, NULL);

	ck_assert_int_eq(code, MATRIX_CALC_ERROR);
}
END_TEST

START_TEST(test_9)
{
	s21_matrix A;
	s21_matrix B;
	s21_matrix result;
	s21_matrix expected;

	double array1[4] = {0.0001, 2.3, 0.030, 11.6};
	double array2[4] = {1.0, 13.044, 96.0, 4.3};
	double expected_array[4] = {1.0001, 15.344, 96.030, 15.9};

	int rows = 2;
	int cols = 2;

	s21_create_test_matrices(&A, &B, &result, &expected,
			rows, cols, array1, array2, expected_array);

	s21_sum_matrix(&A, &B, &result);

	int code = s21_eq_matrix(&result, &expected);
	
	s21_remove_test_matrices(&A, &B, &result, &expected);

	ck_assert_int_eq(code, EQ);
}
END_TEST


TCase* s21_sum_matrix_test_case()
{
	TCase* tc = tcase_create("s21_sum_matrix");

	tcase_add_test(tc, test_1);
	tcase_add_test(tc, test_2);
	tcase_add_test(tc, test_3);
	tcase_add_test(tc, test_4);
	tcase_add_test(tc, test_5);
	tcase_add_test(tc, test_6);
	tcase_add_test(tc, test_7);
	tcase_add_test(tc, test_8);
	tcase_add_test(tc, test_9);

	return tc;
}
