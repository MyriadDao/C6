#include "../test_cases.h"

START_TEST(test_1)
{
	s21_matrix A = {0};
	s21_create_matrix(3, 3, &A);

	double expected_det = -6.0;

	double array_A[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 5.0, 7.0, 8.0, 9.0};

	s21_matrix_from_array(3, 3, 9, array_A, &A);

	double det = 0.0;
	s21_determinant(&A, &det);

	s21_remove_matrix(&A);

	ck_assert((fabs(det) - fabs(expected_det)) < 1e-7);
}
END_TEST

START_TEST(test_2)
{
	s21_matrix A = {0};

	double det = 0.0;
	int status = s21_determinant(&A, &det);

	ck_assert_int_eq(status, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_3)
{
	s21_matrix A = {0};
	s21_create_matrix(3, 5, &A);

	double det = 0.0;
	int status = s21_determinant(&A, &det);

	s21_remove_matrix(&A);

	ck_assert_int_eq(status, MATRIX_CALC_ERROR);
}
END_TEST

START_TEST(test_4)
{
	s21_matrix A = {0};
	s21_create_matrix(2, 2, &A);

	double expected_det = -2.0;

	double array_A[4] = {1.0, 2.0, 3.0, 4.0};

	s21_matrix_from_array(2, 2, 4, array_A, &A);

	double det = 0.0;
	s21_determinant(&A, &det);

	s21_remove_matrix(&A);

	ck_assert((fabs(det) - fabs(expected_det)) < 1e-7);

}
END_TEST

START_TEST(test_5)
{
	s21_matrix A = {0};
	s21_create_matrix(1, 1, &A);

	double expected_det = 1.0;

	double array_A[1] = {1.0};

	s21_matrix_from_array(1, 1, 1, array_A, &A);

	double det = 0.0;
	s21_determinant(&A, &det);

	s21_remove_matrix(&A);

	ck_assert((fabs(det) - fabs(expected_det)) < 1e-7);

}
END_TEST

TCase* s21_determinant_test_case()
{
	TCase* tc = tcase_create("s21_determinant");

	tcase_add_test(tc, test_1);
	tcase_add_test(tc, test_2);
	tcase_add_test(tc, test_3);
	tcase_add_test(tc, test_4);
	tcase_add_test(tc, test_5);

	return tc;
}
