#include "matrix_suite.h"

Suite* matrix_suite()
{
	Suite* suite;

	suite = suite_create("s21_matrix");

	suite_add_tcase(suite, s21_create_matrix_test_case());
	suite_add_tcase(suite, s21_remove_matrix_test_case());

	suite_add_tcase(suite, s21_sum_matrix_test_case());

	return suite;
}
