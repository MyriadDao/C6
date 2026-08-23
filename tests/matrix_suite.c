#include "matrix_suite.h"

Suite* matrix_suite()
{
	Suite* suite;

	suite = suite_create("s21_matrix");

	suite_add_tcase(suite, s21_create_matrix_test_case());
	suite_add_tcase(suite, s21_sum_matrix_test_case());
	suite_add_tcase(suite, s21_sub_matrix_test_case());
	suite_add_tcase(suite, s21_mult_number_test_case());
	suite_add_tcase(suite, s21_mult_matrix_test_case());

	suite_add_tcase(suite, s21_eq_matrix_test_case());

	suite_add_tcase(suite, s21_transpose_test_case());
	suite_add_tcase(suite, s21_calc_complements_test_case());
	suite_add_tcase(suite, s21_determinant_test_case());
	suite_add_tcase(suite, s21_inverse_matrix_test_case());

	return suite;
}
