#include "../test_cases.h"

START_TEST(test_1)
{
	s21_matrix A = {0};
	s21_matrix B = {0};
	s21_create_matrix(2, 2, &A);
	s21_create_matrix(2, 2, &B);

	double array_A[4] = {1.0, 2.0, 3.0, 4.0};
	double array_B[4] = {1.0, 2.0, 3.0, 4.0};

	s21_matrix_from_array(2, 2, 4, array_A, &A);
	s21_matrix_from_array(2, 2, 4, array_B, &B);

	int result = s21_eq_matrix(&A, &B);

	s21_remove_matrix(&A);
	s21_remove_matrix(&B);

	ck_assert_int_eq(result, EQ);
}
END_TEST

START_TEST(test_2)
{
	s21_matrix A = {0};
	s21_matrix B = {0};
	s21_create_matrix(3, 4, &A);
	s21_create_matrix(3, 4, &B);

	double array_A[12] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
	double array_B[12] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};

	s21_matrix_from_array(3, 4, 12, array_A, &A);
	s21_matrix_from_array(3, 4, 12, array_B, &B);

	int result = s21_eq_matrix(&A, &B);

	s21_remove_matrix(&A);
	s21_remove_matrix(&B);

	ck_assert_int_eq(result, EQ);
}
END_TEST

START_TEST(test_3)
{
	s21_matrix A = {0};
	s21_matrix B = {0};
	s21_create_matrix(1, 1, &A);

	int result = s21_eq_matrix(&A, &B);

	s21_remove_matrix(&A);

	ck_assert_int_eq(result, N_EQ);
}
END_TEST


START_TEST(test_4)
{
	s21_matrix A = {0};
	s21_matrix B = {0};
	s21_create_matrix(1, 1, &B);

	int result = s21_eq_matrix(&A, &B);

	s21_remove_matrix(&B);

	ck_assert_int_eq(result, N_EQ);
}
END_TEST


START_TEST(test_5)
{
	s21_matrix A = {0};
	s21_matrix B = {0};
	s21_create_matrix(3, 1, &A);
	s21_create_matrix(1, 1, &B);

	int result = s21_eq_matrix(&A, &B);

	s21_remove_matrix(&A);
	s21_remove_matrix(&B);

	ck_assert_int_eq(result, N_EQ);
}
END_TEST


START_TEST(test_6)
{
	s21_matrix A = {0};
	s21_matrix B = {0};
	s21_create_matrix(1, 1, &A);
	s21_create_matrix(1, 2, &B);

	int result = s21_eq_matrix(&A, &B);

	s21_remove_matrix(&A);
	s21_remove_matrix(&B);

	ck_assert_int_eq(result, N_EQ);
}
END_TEST


TCase* s21_eq_matrix_test_case()
{
	TCase* tc = tcase_create("s21_eq_matrix");
	
	tcase_add_test(tc, test_1);
	tcase_add_test(tc, test_2);
	tcase_add_test(tc, test_3);
	tcase_add_test(tc, test_4);
	tcase_add_test(tc, test_5);
	tcase_add_test(tc, test_6);

	return tc;
}
