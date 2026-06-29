#include "../test_cases.h"

START_TEST(test_1)
{
	s21_matrix A = {0};
	s21_matrix complements = {0};
	s21_matrix expected = {0};

	double array_A[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
	double array_expected[9] = {-3, 6, -3, 6, -12, 6, -3, 6, -3};

	s21_create_test_matrices(&A, NULL, &complements, &expected, 
			         3, 3, array_A, NULL, array_expected);

	s21_calc_complements(&A, &complements);
	int result = s21_eq_matrix(&complements, &expected);

	s21_remove_test_matrices(&A, NULL, &complements, &expected);

	ck_assert_int_eq(result, EQ);
}
END_TEST

START_TEST(test_2)
{
	s21_matrix A = {0};
	s21_create_matrix(1, 1, &A);

	int status = s21_calc_complements(&A, NULL);

	s21_remove_matrix(&A);

	ck_assert_int_eq(status, MATRIX_OP_ERROR);
}
END_TEST

START_TEST(test_3)
{
	s21_matrix complements = {0};
	s21_create_matrix(1, 1, &complements);

	int status = s21_calc_complements(NULL, &complements);

	s21_remove_matrix(&complements);

	ck_assert_int_eq(status, MATRIX_OP_ERROR);

}
END_TEST

START_TEST(test_4)
{
	s21_matrix A = {0};
	s21_matrix complements = {0};

	s21_create_matrix(2, 3, &A);
	s21_create_matrix(2, 2, &complements);

	int status = s21_calc_complements(&A, &complements);

	s21_remove_matrix(&A);
	s21_remove_matrix(&complements);

	ck_assert_int_eq(status, MATRIX_CALC_ERROR);
}
END_TEST

START_TEST(test_5)
{
	s21_matrix A = {0};
	s21_matrix complements = {0};

	s21_create_matrix(2, 2, &A);
	s21_create_matrix(2, 4, &complements);

	int status = s21_calc_complements(&A, &complements);

	s21_remove_matrix(&A);
	s21_remove_matrix(&complements);

	ck_assert_int_eq(status, MATRIX_CALC_ERROR);
}
END_TEST

TCase* s21_calc_complements_test_case()
{
	TCase* tc = tcase_create("s21_calc_complements");

	tcase_add_test(tc, test_1);
	tcase_add_test(tc, test_2);
	tcase_add_test(tc, test_3);
	tcase_add_test(tc, test_4);
	tcase_add_test(tc, test_5);

	return tc;
}
