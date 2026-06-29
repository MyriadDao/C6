#include "../test_cases.h"

START_TEST(test_1)
{
	s21_matrix A;
	int code = s21_create_matrix(2, 2, &A);

	s21_remove_matrix(&A);

	ck_assert_int_eq(code, MATRIX_OP_OK);
}
END_TEST

START_TEST(test_2)
{
	s21_matrix A;
	int code = s21_create_matrix(5, 5, &A);

	s21_remove_matrix(&A);

	ck_assert_int_eq(code, MATRIX_OP_OK);
}
END_TEST

START_TEST(test_3)
{
	s21_matrix A;
	int code = s21_create_matrix(2, 0, &A);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_4)
{
	s21_matrix A;
	int code = s21_create_matrix(0, 2, &A);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_5)
{
	s21_matrix A;
	int code = s21_create_matrix(0, 0, &A);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_6)
{
	int code = s21_create_matrix(2, 2, NULL);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

TCase* s21_create_matrix_test_case()
{
	TCase* tc = tcase_create("s21_create_matrix");

	tcase_add_test(tc, test_1);
	tcase_add_test(tc, test_2);
	tcase_add_test(tc, test_3);
	tcase_add_test(tc, test_4);
	tcase_add_test(tc, test_5);
	tcase_add_test(tc, test_6);

	return tc;
}
