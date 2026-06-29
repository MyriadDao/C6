#include "../test_cases.h"

START_TEST(test_1)
{
	s21_matrix A;
	s21_matrix result;
	s21_matrix expected;

	double array1[4] = {1.0, 2.0, 3.0, 4.0};
	double number = 2;
	double expected_array[4] = {2.0, 4.0, 6.0, 8.0};

	int rows = 2;
	int cols = 2;

	s21_create_test_matrices(&A, NULL, &result, &expected,
			rows, cols, array1, NULL, expected_array);

	s21_mult_number(&A, number, &result);

	int code = s21_eq_matrix(&result, &expected);
	
	s21_remove_test_matrices(&A, NULL, &result, &expected);

	ck_assert_int_eq(code, EQ);
}
END_TEST

START_TEST(test_2)
{
	s21_matrix A = {0};
	s21_matrix result = {0};


	int code = s21_mult_number(&A, 1, &result);

	s21_remove_test_matrices(&A, NULL, &result, NULL);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_3)
{
	s21_matrix A = {0};
	s21_matrix result;

	s21_create_matrix(1, 1, &result);

	int code = s21_mult_number(&A, 1, &result);

	s21_remove_test_matrices(&A, NULL, &result, NULL);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_4)
{
	s21_matrix A;
	s21_matrix result = {0};

	s21_create_matrix(1, 1, &A);

	int code = s21_mult_number(&A, 1, &result);

	s21_remove_test_matrices(&A, NULL, &result, NULL);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_5)
{
	s21_matrix A;
	s21_matrix result;

	int rows = 2;
	int cols = 2;

	s21_create_matrix(rows, 1, &A);
	s21_create_matrix(rows, cols, &result);

	int code = s21_mult_number(&A, 1, &result);
	
	s21_remove_test_matrices(&A, NULL, &result, NULL);

	ck_assert_int_eq(code, MATRIX_CALC_ERROR);
}
END_TEST

START_TEST(test_6)
{
	s21_matrix A;
	s21_matrix result;

	int rows = 2;
	int cols = 2;

	s21_create_matrix(rows, cols, &A);
	s21_create_matrix(1, cols, &result);

	int code = s21_mult_number(&A, 1, &result);
	
	s21_remove_test_matrices(&A, NULL, &result, NULL);

	ck_assert_int_eq(code, MATRIX_CALC_ERROR);
}
END_TEST

START_TEST(test_7)
{
	s21_matrix A;
	s21_matrix result;
	s21_matrix expected;

	double array1[4] = {0.0001, 2.3, 0.030, 11.6};
	double number = 3.789;
	double expected_array[4] = {0.0003789, 8.7147, 0.11367, 43.9524};

	int rows = 2;
	int cols = 2;

	s21_create_test_matrices(&A, NULL, &result, &expected,
			rows, cols, array1, NULL, expected_array);

	s21_mult_number(&A, number, &result);

	int code = s21_eq_matrix(&result, &expected);
	
	s21_remove_test_matrices(&A, NULL, &result, &expected);

	ck_assert_int_eq(code, EQ);
}
END_TEST


TCase* s21_mult_number_test_case()
{
	TCase* tc = tcase_create("s21_mult_number");

	tcase_add_test(tc, test_1);
	tcase_add_test(tc, test_2);
	tcase_add_test(tc, test_3);
	tcase_add_test(tc, test_4);
	tcase_add_test(tc, test_5);
	tcase_add_test(tc, test_6);
	tcase_add_test(tc, test_7);

	return tc;
}
