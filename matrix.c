#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errorcode.h"
#include "matrix.h"



Matrix* _create_zero_matrix(int n_rows, int n_cols, Ring* ring_inf)
{
	if(n_cols == 0 || n_rows == 0){
		raise_error(INVALID_INPUT, "Matrix couldn't contain zero rows or columns");
	}
	Matrix* new_matrix = (Matrix*)malloc(sizeof(Matrix));
	new_matrix->n_cols = n_cols;
	new_matrix->n_rows = n_rows;
	new_matrix->ring_inf = ring_inf;
	new_matrix->matrix_ptr = calloc(n_rows*n_cols, ring_inf->size);
	if(!new_matrix->matrix_ptr){
		raise_error(MEM_ALLOC_FAIL, "Failed to allocate memory");
	}
	return new_matrix;
}


void print_matrix(Matrix* matrix)
{
	int cols = matrix->n_cols;
	int rows = matrix->n_rows;
	int m_size = rows*cols;
	for(int i=0; i<m_size; i++){
		void *el = matrix->matrix_ptr + i*matrix->ring_inf->size;
		matrix->ring_inf->print_el(el);
		printf(" ");
		if((i+1) % cols == 0){
			printf("\n");
		}
	}
}

//check row_ind>=0
void set_element(Matrix* matrix, void* element, int row_index, int col_index)
{
	if(row_index >= matrix->n_rows || col_index >= matrix->n_cols || row_ind <= 0 || col_ind <= 0){
		raise_error(INVALID_INPUT, "Index out of range");
	}
	int element_size = matrix->ring_inf->size;
	void* dest = matrix->matrix_ptr + (row_index*(matrix->n_cols) +col_index)*element_size;
	memcpy(dest, element, element_size);
}


void* get_element(const Matrix* matrix, int row_index, int col_index)
{
	if(row_index >= matrix->n_rows || col_index >= matrix->n_cols || row_ind <= 0 || col_ind <= 0){
		raise_error(INVALID_INPUT, "Index out of range");
	}
	int element_size = matrix->ring_inf->size;
	void* src = matrix->matrix_ptr + (row_index*(matrix->n_cols) +col_index)*element_size;
	void* res = malloc(element_size);
	if(!res){
		raise_error(MEM_ALLOC_FAIL, "Failed to allocate memory for element");
	}
	memcpy(res, src, element_size);
	return res;
}


Matrix* create_matrix_from_array(int n_rows, int n_cols, void* elements_array, int array_len, Ring* ring_inf)
{
	if(n_rows*n_cols != array_len){
		raise_error(INVALID_INPUT, "Unmatch sizes of array and matrix");
	}
	if(array_len == 0){
		raise_error(INVALID_INPUT, "Matrix couldn't contain zero rows or columns");
	}
	Matrix* new_matrix = _create_zero_matrix(n_rows, n_cols, ring_inf);
	memcpy(new_matrix->matrix_ptr, elements_array, array_len*(ring_inf->size));
	return new_matrix;
}


Matrix* sum_matrix(const Matrix* m1, const Matrix* m2)
{
	if((m1->n_cols != m2->n_cols) || (m1->n_rows != m2->n_rows)){
		raise_error(INVALID_INPUT, "Unmatch sizes of matrix");
	}
	if(m1->ring_inf != m2->ring_inf){
		raise_error(INVALID_INPUT, "Elements in matrix 1 and matrix 2 are different types");
	}
	int res_n_rows = m1->n_rows;
	int res_n_cols = m1->n_cols;
	int m_size = res_n_rows*res_n_cols;
	Matrix* res_matrix = _create_zero_matrix(res_n_rows, res_n_cols, m1->ring_inf);
	if(!res_matrix->matrix_ptr){
		raise_error(MEM_ALLOC_FAIL, "Failed to allocate memory");
	}
	for(int i=0; i<m_size; i++){
		int row_ind = i/res_n_cols;
		int col_ind = i - row_ind*res_n_cols;
		void* element_1 = get_element(m1, row_ind, col_ind);
		void* element_2 = get_element(m2, row_ind, col_ind);
		void* res_element = res_matrix->ring_inf->sum(element_1, element_2);
		set_element(res_matrix, res_element, row_ind, col_ind);
	}
	return res_matrix;
}


Matrix* mult_matrix_to_matrix(const Matrix* m1, const Matrix* m2)
{
	if(m1->n_cols != m2->n_rows){
		raise_error(INVALID_INPUT, "Unmatch sizes of matrix to multiplicate");
	}
	if(m1->ring_inf != m2->ring_inf){
		raise_error(INVALID_INPUT, "Elements in matrix 1 and matrix 2 are different types");
	}
	int res_n_rows = m1->n_rows;
	int res_n_cols = m2->n_cols;
	int m_size = res_n_rows*res_n_cols;
	Matrix* res_matrix = _create_zero_matrix(res_n_rows, res_n_cols, m1->ring_inf);
	if(!res_matrix->matrix_ptr){
		raise_error(MEM_ALLOC_FAIL, "Failed to allocate memory");
	}
	int common_d = m1->n_cols;
	for(int i=0; i<m_size; i++){
		int row_ind = i/res_n_cols;
		int col_ind = i - row_ind*res_n_cols;
		void* res_element = res_matrix->ring_inf->zero;
		for(int k=0; k<common_d; k++){
			void* element_1 = get_element(m1, row_ind, k);
			void* element_2 = get_element(m2, k, i%res_n_cols);
			void* add = res_matrix->ring_inf->mult(element_1, element_2);
			res_element = res_matrix->ring_inf->sum(res_element, add);
		}
		set_element(res_matrix, res_element, row_ind, col_ind);

	}
	return res_matrix;
}


void transpose_matrix(Matrix* matrix)
{
	int element_size = matrix->ring_inf->size;
	int mn_cols = matrix->n_cols;
	int mn_rows = matrix->n_rows;
	int m_size = mn_rows*mn_cols;
	void* transposed_matrix_ptr = malloc(m_size*element_size);
	if(!transposed_matrix_ptr){
		raise_error(MEM_ALLOC_FAIL, "Failed to allocate memory");
	}
	for(int i=0; i<m_size; i++){
		int row_ind = i/mn_cols;
		int col_ind = i - row_ind*mn_cols;
		void* element_1 = get_element(matrix, row_ind, col_ind);
		void* dest = transposed_matrix_ptr + (col_ind*mn_rows + row_ind)*element_size;
		memcpy(dest, element_1, element_size);
	}
	matrix->n_cols = mn_rows;
	matrix->n_rows = mn_cols;
	free(matrix->matrix_ptr);
	matrix->matrix_ptr = transposed_matrix_ptr;
}


Matrix* mult_matrix_to_num(const Matrix* matrix, void* number)
{
	int res_n_rows = matrix->n_rows;
	int res_n_cols = matrix->n_cols;
	int m_size = res_n_rows*res_n_cols;
	Matrix* res_matrix = _create_zero_matrix(res_n_rows, res_n_cols, matrix->ring_inf);
	if(!res_matrix->matrix_ptr){
		raise_error(MEM_ALLOC_FAIL, "Failed to allocate memory");
	}
	for(int i=0; i<m_size; i++){
		int row_ind = i/res_n_cols;
		int col_ind = i - row_ind*res_n_cols;
		void* element = get_element(matrix, row_ind, col_ind);
		void* res_element = res_matrix->ring_inf->mult(element, number);
		set_element(res_matrix, res_element, row_ind, col_ind);
	}
	return res_matrix;
}


void delete_matrix(Matrix* matrix)
{
	free(matrix->matrix_ptr);
	free(matrix);
}