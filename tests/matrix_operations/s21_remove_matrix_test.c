#include "../test_cases.h"

START_TEST(test_1)
{
	s21_matrix A;
	s21_create_matrix(2, 2, &A);

	int code = s21_remove_matrix(&A);

	ck_assert_int_eq(code, MATRIX_OP_OK);
}
END_TEST

START_TEST(test_2)
{
	int code = s21_remove_matrix(NULL);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_3)
{
	s21_matrix A = {0};

	int code = s21_remove_matrix(&A);

	ck_assert_int_eq(code, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_4)
{
	s21_matrix A;
	s21_create_matrix(5, 5, &A);

	int code = s21_remove_matrix(&A);

	ck_assert_int_eq(code, MATRIX_OP_OK);
}
END_TEST

TCase* s21_remove_matrix_test_case()
{
	TCase* tc = tcase_create("s21_remove_matrix");


	tcase_add_test(tc, test_1);
	tcase_add_test(tc, test_2);
	tcase_add_test(tc, test_3);
	tcase_add_test(tc, test_4);

	return tc;
}
