#include "../test_cases.h"

START_TEST(test_1)
{
	s21_matrix A = {0};
	s21_matrix inverse = {0};
	s21_matrix expected = {0};

	double array_A[9] = {0.0, 2.0, 3.0, 3.0, 4.0, 5.0, 7.0, 8.0, 9.0};
	double array_expected[9] = {-1, 1.5, -0.5, 2, -5.25, 2.25, -1, 3.5, -1.5};

	s21_create_test_matrices(&A, NULL, &inverse, &expected, 
			         3, 3, array_A, NULL, array_expected);

	s21_inverse_matrix(&A, &inverse);
	int result = s21_eq_matrix(&inverse, &expected);

	s21_remove_test_matrices(&A, NULL, &inverse, &expected);

	ck_assert_int_eq(result, EQ);
}
END_TEST

START_TEST(test_2)
{
	s21_matrix A = {0};
	s21_create_matrix(1, 1, &A);

	int status = s21_inverse_matrix(&A, NULL);

	s21_remove_matrix(&A);

	ck_assert_int_eq(status, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_3)
{
	s21_matrix inverse = {0};
	s21_create_matrix(1, 1, &inverse);

	int status = s21_inverse_matrix(NULL, &inverse);

	s21_remove_matrix(&inverse);

	ck_assert_int_eq(status, MATRIX_OP_ERROR);

}
END_TEST

START_TEST(test_4)
{
	s21_matrix A = {0};
	s21_matrix inverse = {0};

	s21_create_matrix(2, 3, &A);
	s21_create_matrix(2, 2, &inverse);

	int status = s21_inverse_matrix(&A, &inverse);

	s21_remove_matrix(&A);
	s21_remove_matrix(&inverse);

	ck_assert_int_eq(status, MATRIX_CALC_ERROR);
}
END_TEST

START_TEST(test_5)
{
	s21_matrix A = {0};
	s21_matrix inverse = {0};

	s21_create_matrix(2, 2, &A);
	s21_create_matrix(2, 4, &inverse);

	int status = s21_inverse_matrix(&A, &inverse);

	s21_remove_matrix(&A);
	s21_remove_matrix(&inverse);

	ck_assert_int_eq(status, MATRIX_CALC_ERROR);
}
END_TEST

START_TEST(test_6)
{
	s21_matrix A = {0};
	s21_matrix inverse = {0};

	double array_A[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

	s21_create_test_matrices(&A, NULL, &inverse, NULL, 
			         3, 3, array_A, NULL, NULL);

	int result = s21_inverse_matrix(&A, &inverse);

	s21_remove_test_matrices(&A, NULL, &inverse, NULL);

	ck_assert_int_eq(result, MATRIX_CALC_ERROR);
}
END_TEST

TCase* s21_inverse_matrix_test_case()
{
	TCase* tc = tcase_create("s21_inverse_matrix");

	tcase_add_test(tc, test_1);
	tcase_add_test(tc, test_2);
	tcase_add_test(tc, test_3);
	tcase_add_test(tc, test_4);
	tcase_add_test(tc, test_5);
	tcase_add_test(tc, test_6);

	return tc;
}
