#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"
#include "intinfo.h"
#include "matrix.h"
#include "ring.h"

//indices
enum int_answer_array_indices
{
    sum_two_int,
    mult_two_int,
    mult_int_to_num,
    sum_two_int_one_d,
    mult_int_to_int_one_d,
    transpose_int,
    transpose_int_one_d,
    mult_int_one_d_to_one_d
};


enum compl_answer_array_indices
{
    sum_two_compl,
    mult_two_compl,
    mult_compl_to_num,
    sum_two_compl_one_d,
    mult_compl_to_compl_one_d,
    transpose_compl,
    transpose_compl_one_d,
    mult_copml_one_d_to_one_d
};


Matrix** create_basic_example_matrixes()
{
	Matrix** matrixes_array = (Matrix**)malloc(10*sizeof(Matrix*));
	Ring* int_ring = get_int_ring();
	Ring* complex_ring = get_complex_ring();
	int* arr0  = (int*)malloc(6*sizeof(int));
	arr0[0] = 9;
	arr0[1] = 1;
	arr0[2] = 8;
	arr0[3] = 1;
	arr0[4] = 2;
	arr0[5] = 6;
	int* arr1 = (int*)malloc(6*sizeof(int));
	arr1[0] = 1;
	arr1[1] = 8;
	arr1[2] = 4;
	arr1[3] = 3;
	arr1[4] = 5;
	arr1[5] = 7;
	int* arr2 = (int*)malloc(12*sizeof(int));
	arr2[0] = 2;
	arr2[1] = 2;
	arr2[2] = 1;
	arr2[3] = 0;
	arr2[4] = 3;
	arr2[5] = 2;
	arr2[6] = 1;
	arr2[7] = 0;
	arr2[8] = 2;
	arr2[9] = 1;
	arr2[10] = 3;
	arr2[11] = 1;
	int* arr3 = (int*)malloc(3*sizeof(int));
	arr3[0] = 1;
	arr3[1] = 2;
	arr3[2] = 5;
	int* arr4 = (int*)malloc(3*sizeof(int));
	arr4[0] = 1;
	arr4[1] = 1;
	arr4[2] = 1;
	Complex* carr0 = (Complex*)malloc(6*sizeof(Complex));
	carr0[0] = create_new_complex(1.2, 0.6);
	carr0[1] = create_new_complex(2.5, 3);
	carr0[2] = create_new_complex(1, 1.8);
	carr0[3] = create_new_complex(0, 6);
	Complex* carr1 = (Complex*)malloc(4*sizeof(Complex));
	carr1[0] = create_new_complex(2, 1.3);
	carr1[1] = create_new_complex(5.7, 4.4);
	carr1[2] = create_new_complex(1, 1);
	carr1[3] = create_new_complex(1, 0.5);
	Complex* carr2 = (Complex*)malloc(6*sizeof(Complex));
	carr2[0] = create_new_complex(1.7, 0.5);
	carr2[1] = create_new_complex(1.5, 3.4);
	carr2[2] = create_new_complex(1, 1);
	carr2[3] = create_new_complex(0, 3);
	carr2[4] = create_new_complex(1, 0);
	carr2[5] = create_new_complex(3.6, 2);
	Complex* carr3 = (Complex*)malloc(2*sizeof(Complex));
	carr3[0] = create_new_complex(1, 0.6);
	carr3[1] = create_new_complex(2.1, 3);
	Complex* carr4 = (Complex*)malloc(2*sizeof(Complex));
	carr4[0] = create_new_complex(5.1, 1.3);
	carr4[1] = create_new_complex(2, 0.4);
	matrixes_array[0] = create_matrix_from_array(2, 3, arr0, 6, int_ring);
	matrixes_array[1] = create_matrix_from_array(2, 3, arr1, 6, int_ring);
	matrixes_array[2] = create_matrix_from_array(3, 4, arr2, 12, int_ring);
	matrixes_array[3] = create_matrix_from_array(1, 3, arr3, 3, int_ring);
	matrixes_array[4] = create_matrix_from_array(1, 3, arr4, 3, int_ring);
	matrixes_array[5] = create_matrix_from_array(2, 2, carr0, 4, complex_ring);
	matrixes_array[6] = create_matrix_from_array(2, 2, carr1, 4, complex_ring);
	matrixes_array[7] = create_matrix_from_array(2, 3, carr2, 6, complex_ring);
	matrixes_array[8] = create_matrix_from_array(1, 2, carr3, 2, complex_ring);
	matrixes_array[9] = create_matrix_from_array(1, 2, carr4, 2, complex_ring);
	return matrixes_array;
}


Complex** array_of_compl_answers()
{
	Complex** answers = (Complex**)malloc(8*sizeof(Complex*));
	Complex* sum_m = (Complex*)malloc(4*sizeof(Complex));
	sum_m[0] = create_new_complex(3.2, 1.9);
	sum_m[1] = create_new_complex(8.2, 7.4);
	sum_m[2] = create_new_complex(2, 2.8);
	sum_m[3] = create_new_complex(1, 6.5);
	Complex* mult_m_m = (Complex*)malloc(6*sizeof(Complex));
	mult_m_m[0] = create_new_complex(-7.26, 9.12);
	mult_m_m[1] = create_new_complex(2.26, 7.98);
	mult_m_m[2] = create_new_complex(3.6, 17.6);
	mult_m_m[3] = create_new_complex(-17.2, 3.56);
	mult_m_m[4] = create_new_complex(-4.62, 12.1);
	mult_m_m[5] = create_new_complex(-12.8, 24.4);
	Complex* mult_m_n = (Complex*)malloc(4*sizeof(Complex));
	mult_m_n[0] = create_new_complex(0, 1.5); 
	mult_m_n[1] = create_new_complex(-1.75, 4);
	mult_m_n[2] = create_new_complex(-1.3, 1.9);
	mult_m_n[3] = create_new_complex(-6, 3);
	Complex* sum_1d = (Complex*)malloc(2*sizeof(Complex));
	sum_1d[0] = create_new_complex(6.1, 1.9); 
	sum_1d[1] = create_new_complex(4.1, 1.4);
	Complex* mult_1d_to_m = (Complex*)malloc(3*sizeof(Complex));
	mult_1d_to_m[0] = create_new_complex(-7.6, 7.8); 
	mult_1d_to_m[1] = create_new_complex(1.56, 7.3);
	mult_1d_to_m[2] = create_new_complex(1.96, 16.6);
	Complex* transpose_m = (Complex*)malloc(4*sizeof(Complex));
	transpose_m[0] = create_new_complex(1.2, 0.6);
	transpose_m[1] = create_new_complex(1, 1.8);
	transpose_m[2] = create_new_complex(2.5, 3);
	transpose_m[3] = create_new_complex(0, 6);
	Complex* transpose_1d = (Complex*)malloc(2*sizeof(Complex));
	transpose_1d[0] = create_new_complex(1, 0.6); 
	transpose_1d[1] = create_new_complex(2.1, 3);
	Complex* mult_1d_1d = (Complex*)malloc(sizeof(Complex));
	mult_1d_1d[0] = create_new_complex(7.32, 11.2);
	answers[0] = sum_m;
	answers[1] = mult_m_m;
	answers[2] = mult_m_n;
	answers[3] = sum_1d;
	answers[4] = mult_1d_to_m;
	answers[5] = transpose_m;
	answers[6] = transpose_1d;
	answers[7] = mult_1d_1d;
	return answers; 
}


int** array_of_int_answers()
{
	int** answers = (int**)malloc(8*sizeof(int*));
	int* sum_m = (int*)malloc(6*sizeof(int));
	sum_m[0] = 10;
	sum_m[1] = 9;
	sum_m[2] = 12;
	sum_m[3] = 4;
	sum_m[4] = 7;
	sum_m[5] = 13;
	int* mult_m_m = (int*)malloc(8*sizeof(int));
	mult_m_m[0] = 37;
	mult_m_m[1] = 28;
	mult_m_m[2] = 34;
	mult_m_m[3] = 8;
	mult_m_m[4] = 20;
	mult_m_m[5] = 12;
	mult_m_m[6] = 21;
	mult_m_m[7] = 6;
	int* mult_m_n = (int*)malloc(6*sizeof(int));
	mult_m_n[0] = 18; 
	mult_m_n[1] = 2;
	mult_m_n[2] = 16;
	mult_m_n[3] = 2;
	mult_m_n[4] = 4;
	mult_m_n[5] = 12;
	int* sum_1d = (int*)malloc(3*sizeof(int));
	sum_1d[0] = 2; 
	sum_1d[1] = 3;
	sum_1d[2] = 6;
	int* mult_1d_to_m = (int*)malloc(4*sizeof(int));
	mult_1d_to_m[0] = 18; 
	mult_1d_to_m[1] = 11;
	mult_1d_to_m[2] = 18;
	mult_1d_to_m[3] = 5;
	int* transpose_m = (int*)malloc(6*sizeof(int));
	transpose_m[0] = 9;
	transpose_m[1] = 1;
	transpose_m[2] = 1;
	transpose_m[3] = 2;
	transpose_m[4] = 8;
	transpose_m[5] = 6;
	int* transpose_1d = (int*)malloc(3*sizeof(int));
	transpose_1d[0] = 1; 
	transpose_1d[1] = 2;
	transpose_1d[2] = 5;
	int* mult_1d_1d = (int*)malloc(sizeof(int));
	mult_1d_1d[0] = 8;
	answers[0] = sum_m;
	answers[1] = mult_m_m;
	answers[2] = mult_m_n;
	answers[3] = sum_1d;
	answers[4] = mult_1d_to_m;
	answers[5] = transpose_m;
	answers[6] = transpose_1d;
	answers[7] = mult_1d_1d;
	return answers; 
}


int compare_complex_m(Complex* a1, Complex* a2, int len)
{
	int check = memcmp(a1, a2, len);
	return check;
}


void run_tests()
{
	Ring* complex_ring = get_complex_ring();
	Matrix** ar = create_basic_example_matrixes();
	int** int_answ = array_of_int_answers();
	Complex** compl_answ = array_of_compl_answers();
	int int_num = 2;
	Complex compl_num = create_new_complex(0.5, 1);
	Matrix* mi1 = sum_matrix(ar[0],ar[1]);
	enum int_answer_array_indices answ_ind1 = sum_two_int;
	assert(!memcmp(mi1->matrix_ptr, int_answ[answ_ind1], 6*sizeof(int)));
	printf("Test sum of integer matrixes: OK\n");
	Matrix* mi2 = mult_matrix_to_matrix(ar[0], ar[2]);
	enum int_answer_array_indices answ_ind2 = mult_two_int;
	assert(!memcmp(mi2->matrix_ptr, int_answ[answ_ind2], 8*sizeof(int)));
	printf("Test mult of two integer matrixes: OK\n");
	Matrix* mi3 = mult_matrix_to_num(ar[0], &int_num);
	enum int_answer_array_indices answ_ind3 = mult_int_to_num;
	assert(!memcmp(mi3->matrix_ptr, int_answ[answ_ind3], 6*sizeof(int)));
	printf("Test mult integer matrix to num: OK\n");
	Matrix* mi4 = sum_matrix(ar[3], ar[4]);
	enum int_answer_array_indices answ_ind4 = sum_two_int_one_d;
	assert(!memcmp(mi4->matrix_ptr, int_answ[answ_ind4], 3*sizeof(int)));
	printf("Test sum of integer matrixes with 1 row: OK\n");
	Matrix* mi5 = mult_matrix_to_matrix(ar[3], ar[2]);
	enum int_answer_array_indices answ_ind5 = mult_int_to_int_one_d;
	assert(!memcmp(mi5->matrix_ptr, int_answ[answ_ind5], 4*sizeof(int)));
	printf("Test mult of integer matrix and row: OK\n");
	transpose_matrix(ar[0]);
	enum int_answer_array_indices answ_ind6 = transpose_int;
	assert(!memcmp(ar[0]->matrix_ptr, int_answ[answ_ind6], 6*sizeof(int)));
	printf("Test transpose integer matrix: OK\n");
	transpose_matrix(ar[3]);
	enum int_answer_array_indices answ_ind7 = transpose_int_one_d;
	assert(!memcmp(ar[3]->matrix_ptr, int_answ[answ_ind7], 3*sizeof(int)));
	printf("Test transpose integer matrix with 1 row: OK\n");
	Matrix* mi6 = mult_matrix_to_matrix(ar[4], ar[3]);
	enum int_answer_array_indices answ_ind8 = mult_int_one_d_to_one_d;
	assert(!memcmp(mi6->matrix_ptr, int_answ[answ_ind8], 1*sizeof(int)));
	printf("Test mult of integer matrix with 1 row and matrix with 1 col: OK\n");
	Matrix* mc1 = sum_matrix(ar[5],ar[6]);
	enum compl_answer_array_indices answ_ind11 = sum_two_compl;
	assert(!compare_complex_m((Complex*)mc1->matrix_ptr, compl_answ[answ_ind11], 4));
	printf("Test sum of complex matrixes: OK\n");
	Matrix* mc2 = mult_matrix_to_matrix(ar[5], ar[7]);
	enum compl_answer_array_indices answ_ind22 = mult_two_compl;
	assert(!compare_complex_m((Complex*)mc2->matrix_ptr, compl_answ[answ_ind22], 6));
	printf("Test mult of two complex matrixes: OK\n");
	Matrix* mc3 = mult_matrix_to_num(ar[5], &compl_num);
	enum compl_answer_array_indices answ_ind33 = mult_compl_to_num;
	assert(!compare_complex_m((Complex*)mc3->matrix_ptr, compl_answ[answ_ind33], 4));
	printf("Test mult complex matrix to num: OK\n");
	Matrix* mc4 = sum_matrix(ar[8], ar[9]);
	enum compl_answer_array_indices answ_ind44 = sum_two_compl_one_d;
	assert(!compare_complex_m((Complex*)mc4->matrix_ptr, compl_answ[answ_ind44], 2));
	printf("Test sum of complex matrixes with 1 row: OK\n");
	Matrix* mc5 = mult_matrix_to_matrix(ar[8], ar[7]);
	enum compl_answer_array_indices answ_ind55 = mult_compl_to_compl_one_d;
	assert(!compare_complex_m((Complex*)mc5->matrix_ptr, compl_answ[answ_ind55], 3));
	printf("Test mult of complex matrix and row: OK\n");
	transpose_matrix(ar[5]);
	enum compl_answer_array_indices answ_ind66 = transpose_compl;
	assert(!compare_complex_m((Complex*)ar[5]->matrix_ptr, compl_answ[answ_ind66], 4));
	printf("Test transpose complex matrix: OK\n");
	transpose_matrix(ar[8]);
	enum compl_answer_array_indices answ_ind77 = transpose_compl_one_d;
	assert(!compare_complex_m((Complex*)ar[8]->matrix_ptr, compl_answ[answ_ind77], 2));
	printf("Test transpose complex matrix with 1 row: OK\n");
	Matrix* mc6 = mult_matrix_to_matrix(ar[9], ar[8]);
	enum compl_answer_array_indices answ_ind88 = mult_copml_one_d_to_one_d;
	Complex el = *compl_answ[answ_ind88];
	Complex el2 = *(Complex*)mc6->matrix_ptr;
	void* el3 = complex_ring->sum(&el, complex_ring->minus(&el2));
	assert(!((Complex*)complex_ring->zero == (Complex*)el3));
	printf("Test mult of complex matrix with 1 row and matrix with 1 col: OK\n");
}