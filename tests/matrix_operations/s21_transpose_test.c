#include "../test_cases.h"

START_TEST(test_1)
{
	s21_matrix A = {0};
	s21_matrix result = {0};
	s21_matrix expected = {0};

	int rows = 2;
	int cols = 2;

	double array_A[4] = {1.0, 2.0, 3.0, 4.0};
	double array_expected[4] = {1.0, 3.0, 2.0, 4.0};

	s21_create_matrix(cols, rows, &result);
	s21_matrix_from_array(rows, cols, rows*cols, array_A, &A);
	s21_matrix_from_array(rows, cols, rows*cols, array_expected, &expected);

	s21_transpose(&A, &result);

	int code = s21_eq_matrix(&result, &expected);

	s21_remove_test_matrices(&A, NULL, &result, &expected);

	ck_assert_int_eq(code, EQ);
}
END_TEST

START_TEST(test_2)
{
	s21_matrix A = {0};
	s21_matrix result = {0};

	int code = s21_transpose(&A, &result);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_3)
{
	s21_matrix A = {0};
	s21_matrix result = {0};

	int code = s21_transpose(&A, &result);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_4)
{
	s21_matrix A = {0};
	s21_matrix result;

	int code = s21_transpose(&A, &result);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_5)
{
	s21_matrix A;
	s21_matrix result = {0};

	s21_create_matrix(2, 3, &A);

	int code = s21_transpose(&A, &result);

	s21_remove_matrix(&A);
	s21_remove_matrix(&result);

	ck_assert_int_eq(code, MATRIX_OP_OK);
}
END_TEST


START_TEST(test_6)
{
	s21_matrix A = {0};
	s21_matrix result = {0};
	s21_matrix expected = {0};

	int rows = 3;
	int cols = 2;

	double array_A[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
	double array_expected[6] = {1.0, 3.0, 5.0, 2.0, 4.0, 6.0};

	s21_create_matrix(cols, rows, &result);
	s21_matrix_from_array(rows, cols, rows*cols, array_A, &A);
	s21_matrix_from_array(cols, rows, rows*cols, array_expected, &expected);

	s21_transpose(&A, &result);

	int code = s21_eq_matrix(&result, &expected);

	s21_remove_test_matrices(&A, NULL, &result, &expected);

	ck_assert_int_eq(code, EQ);
}
END_TEST

TCase* s21_transpose_test_case()
{
	TCase* tc = tcase_create("s21_transpose");

	tcase_add_test(tc, test_1);
	tcase_add_test(tc, test_2);
	tcase_add_test(tc, test_3);
	tcase_add_test(tc, test_4);
	tcase_add_test(tc, test_5);
	tcase_add_test(tc, test_6);

	return tc;
}
