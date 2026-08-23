#include "s21_matrix.h"

static int s21_is_matrix_valid(const s21_matrix* m) {
  return m != NULL && m->matrix != NULL;
}

static int s21_is_same_size(const s21_matrix* A, const s21_matrix* B) {
  if (!s21_is_matrix_valid(A) || !s21_is_matrix_valid(B)) return 0;
  return A->rows == B->rows && A->columns == B->columns;
}

int s21_create_matrix(int rows, int columns, s21_matrix* result) {
  if (result == NULL) return MATRIX_OP_ERROR;
  int status = (rows <= 0 || columns <= 0) ? MATRIX_OP_ERROR : MATRIX_OP_OK;
  if (status == MATRIX_OP_OK) {
    result->matrix = calloc(rows, sizeof(double*));
    if (result->matrix == NULL) status = MATRIX_OP_ERROR;
  }
  for (int i = 0; i < rows && status == MATRIX_OP_OK; i++) {
    result->matrix[i] = calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) free(result->matrix[j]);
      free(result->matrix);
      status = MATRIX_OP_ERROR;
    }
  }
  if (status == MATRIX_OP_OK) {
    result->rows = rows;
    result->columns = columns;
  } else {
    result->matrix = NULL;
    result->rows = 0;
    result->columns = 0;
  }
  return status;
}

void s21_remove_matrix(s21_matrix* A) {
  if (A == NULL || A->matrix == NULL) return;
  for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(s21_matrix* A, s21_matrix* B) {
  if (!s21_is_matrix_valid(A) || !s21_is_matrix_valid(B)) return N_EQ;
  if (!s21_is_same_size(A, B)) return N_EQ;
  int result = EQ;
  for (int i = 0; i < A->rows && result == EQ; i++) {
    for (int j = 0; j < A->columns && result == EQ; j++) {
      double diff = A->matrix[i][j] - B->matrix[i][j];
      if ((diff < 0.0 ? -diff : diff) >= S21_EPSILON) result = N_EQ;
    }
  }
  return result;
}

int s21_sum_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result) {
  if (!s21_is_matrix_valid(A) || !s21_is_matrix_valid(B) || result == NULL)
    return MATRIX_OP_ERROR;
  if (!s21_is_same_size(A, B)) return MATRIX_CALC_ERROR;
  int status = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows && status == MATRIX_OP_OK; i++)
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
  return status;
}

int s21_sub_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result) {
  if (!s21_is_matrix_valid(A) || !s21_is_matrix_valid(B) || result == NULL)
    return MATRIX_OP_ERROR;
  if (!s21_is_same_size(A, B)) return MATRIX_CALC_ERROR;
  int status = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows && status == MATRIX_OP_OK; i++)
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
  return status;
}

int s21_mult_number(s21_matrix* A, double number, s21_matrix* result) {
  if (!s21_is_matrix_valid(A) || result == NULL) return MATRIX_OP_ERROR;
  int status = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows && status == MATRIX_OP_OK; i++)
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] * number;
  return status;
}

int s21_mult_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result) {
  if (!s21_is_matrix_valid(A) || !s21_is_matrix_valid(B) || result == NULL)
    return MATRIX_OP_ERROR;
  if (A->columns != B->rows) return MATRIX_CALC_ERROR;
  int status = s21_create_matrix(A->rows, B->columns, result);
  for (int i = 0; i < A->rows && status == MATRIX_OP_OK; i++)
    for (int j = 0; j < B->columns; j++)
      for (int k = 0; k < A->columns; k++)
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
  return status;
}

int s21_transpose(s21_matrix* A, s21_matrix* result) {
  if (!s21_is_matrix_valid(A) || result == NULL) return MATRIX_OP_ERROR;
  int status = s21_create_matrix(A->columns, A->rows, result);
  for (int i = 0; i < A->rows && status == MATRIX_OP_OK; i++)
    for (int j = 0; j < A->columns; j++) result->matrix[j][i] = A->matrix[i][j];
  return status;
}

static int s21_get_minor(const s21_matrix* A, int skip_row, int skip_col,
                         s21_matrix* minor) {
  int n = A->rows - 1;
  int status = s21_create_matrix(n, n, minor);
  if (status != MATRIX_OP_OK) return status;
  int mi = 0;
  for (int i = 0; i < A->rows; i++) {
    int mj = 0;
    for (int j = 0; j < A->columns; j++) {
      if (i != skip_row && j != skip_col)
        minor->matrix[mi][mj++] = A->matrix[i][j];
    }
    if (i != skip_row) mi++;
  }
  return MATRIX_OP_OK;
}

static double s21_calc_det(const s21_matrix* A) {
  double det;
  if (A->rows == 1) {
    det = A->matrix[0][0];
  } else if (A->rows == 2) {
    det = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    det = 0.0;
    for (int j = 0; j < A->columns; j++) {
      s21_matrix minor;
      if (s21_get_minor(A, 0, j, &minor) == MATRIX_OP_OK) {
        double sign = (j % 2 == 0) ? 1.0 : -1.0;
        det += sign * A->matrix[0][j] * s21_calc_det(&minor);
        s21_remove_matrix(&minor);
      }
    }
  }
  return det;
}

int s21_determinant(s21_matrix* A, double* result) {
  if (!s21_is_matrix_valid(A) || result == NULL) return MATRIX_OP_ERROR;
  if (A->rows != A->columns) return MATRIX_CALC_ERROR;
  *result = s21_calc_det(A);
  return MATRIX_OP_OK;
}

int s21_calc_complements(s21_matrix* A, s21_matrix* result) {
  if (!s21_is_matrix_valid(A) || result == NULL) return MATRIX_OP_ERROR;
  if (A->rows != A->columns) return MATRIX_CALC_ERROR;
  int status = s21_create_matrix(A->rows, A->columns, result);
  if (A->rows == 1 && status == MATRIX_OP_OK) {
    result->matrix[0][0] = 1.0;
  } else {
    for (int i = 0; i < A->rows && status == MATRIX_OP_OK; i++) {
      for (int j = 0; j < A->columns; j++) {
        s21_matrix minor;
        if (s21_get_minor(A, i, j, &minor) == MATRIX_OP_OK) {
          double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
          result->matrix[i][j] = sign * s21_calc_det(&minor);
          s21_remove_matrix(&minor);
        }
      }
    }
  }
  return status;
}

int s21_inverse_matrix(s21_matrix* A, s21_matrix* result) {
  if (!s21_is_matrix_valid(A) || result == NULL) return MATRIX_OP_ERROR;
  if (A->rows != A->columns) return MATRIX_CALC_ERROR;
  double det = s21_calc_det(A);
  if (det < S21_EPSILON && det > -S21_EPSILON) return MATRIX_CALC_ERROR;
  int status;
  if (A->rows == 1) {
    status = s21_create_matrix(1, 1, result);
    if (status == MATRIX_OP_OK) result->matrix[0][0] = 1.0 / det;
  } else {
    s21_matrix complements;
    status = s21_calc_complements(A, &complements);
    if (status == MATRIX_OP_OK) {
      s21_matrix transposed;
      status = s21_transpose(&complements, &transposed);
      s21_remove_matrix(&complements);
      if (status == MATRIX_OP_OK) {
        status = s21_mult_number(&transposed, 1.0 / det, result);
        s21_remove_matrix(&transposed);
      }
    }
  }
  return status;
}
