#include "ring.h"
#ifndef MATRIX_H
#define MATRIX_H


typedef struct Matrix
{
	int n_rows;
	int n_cols;
	Ring* ring_inf;
	void* matrix_ptr;
} Matrix;


Matrix* _create_zero_matrix(int n_rows, int n_cols, Ring* ring_inf); //create_zero_matrix
void print_matrix(Matrix* matrix);
void set_element(Matrix* matrix, void* element, int row_index, int col_index);
void* get_element(const Matrix* matrix, int row_index, int col_index);
Matrix* create_matrix_from_array(int n_rows, int n_cols, void* elements_array, int array_len, Ring* ring_inf);
Matrix* sum_matrix(const Matrix* m1, const Matrix* m2);
Matrix* mult_matrix_to_matrix(const Matrix* m1, const Matrix* m2);
void transpose_matrix(Matrix* matrix);
Matrix* mult_matrix_to_num(const Matrix* matrix, void* number);
void delete_matrix(Matrix* matrix);


#endif