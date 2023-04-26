#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "complex.h"
#include "errorcode.h"
#include "intinfo.h"
#include "menu.h"
#include "matrix.h"
#include "ring.h"


const char* HELLO_PART = """Welcome to our programm which provides working with matrixes.\n\
You can work with matrixes of integers and matrixes of complex.\n You can't do \
operations between matrixes of different types.\n All avaliable functions are shown in our menu.\n\
Please, be a good user and don't try to do anything unexpected or not permited.""";


void print_base_options(){
	printf("Choose what to do and enter the appropriate number:\n");
	printf("1. Create new matrix\n");
	printf("2. Transpose matrix \n");
	printf("3. Sum two matrixes\n");
	printf("4. Multiply matrix to number\n");
	printf("5. Multiply matrix to matrix\n");
	printf("6. Quit\n");

}


int* int_array_input(int n_rows, int n_cols){
	int* data = (int*)malloc(n_rows*n_cols*sizeof(int));
	if (!data) {
		raise_error(MEM_ALLOC_FAIL, "Failed to allocate memory");
	}
	for (int i=0; i<(n_rows*n_cols); i++){
		printf("Enter element\n");
		int check = scanf("%d", &data[i]);
		if(check != 1){
			raise_error(PERMITED_OPERATION, "You entered bad value");
		}
	}
	return data;
}


Complex* complex_array_input(int n_rows, int n_cols){
	Complex* data = (Complex*)malloc(n_rows*n_cols*sizeof(Complex));
	if (!data) {
		raise_error(MEM_ALLOC_FAIL, "Failed to allocate memory");
	}
	for (int i=0; i<(n_rows*n_cols); i++){
		printf("Enter re and im for complex number\n");
		double re, im; 
		int check = scanf("%lf%lf", &re, &im);
		if(check != 2){
			raise_error(PERMITED_OPERATION, "You entered bad value");
		}
		Complex element = create_new_complex(re, im);
		data[i] = element;
	}
	return data;
}


void clean_mem(Ring** int_ring, Ring** complex_ring, Matrix*** matrixes_array, int len_m_array)
{
	for(int i=0; i<len_m_array; i++){
		delete_matrix(*(*matrixes_array+i));
	}
	free(*matrixes_array);
	free(*int_ring);
	free(*complex_ring);
}


void create_and_print_menu()
{
	system("clear");
	printf(HELLO_PART);
	Ring* int_ring = get_int_ring();
	Ring* complex_ring = get_complex_ring();
	int var = 0;
	int len_m_array = 0;
	Matrix** matrixes_array = NULL;
	while(var !=6){
		print_base_options();
		int check = scanf("%d", &var);
		if(check != 1 || var > 6 || var < 1){
			clean_mem(&int_ring, &complex_ring, &matrixes_array, len_m_array);
			raise_error(PERMITED_OPERATION, "You entered bad value");
		}
		switch(var){
			case 1:{
				len_m_array +=1;
				matrixes_array = (Matrix**)realloc(matrixes_array, len_m_array*sizeof(Matrix*));
				int n_rows = 0;
				int n_cols = 0;
				system("clear");
				printf("Enter number of rows and number of coumns\n");
				int check_nums =scanf("%d%d", &n_rows, &n_cols);
				if(check_nums != 2){
					clean_mem(&int_ring, &complex_ring, &matrixes_array, len_m_array);
					raise_error(PERMITED_OPERATION, "You entered bad value");
				}
				int opt = 0;
				system("clear");
				printf("Choose type of matrix elements\n");
				printf("1. Matrix with integer\n");
				printf("2. Matrix with complex\n");
				int check_opt = scanf("%d", &opt);
				if(check_opt != 1 || opt > 2 || opt < 1){
					clean_mem(&int_ring, &complex_ring, &matrixes_array, len_m_array);
					raise_error(PERMITED_OPERATION, "You entered bad value");
				}
				system("clear");
				printf("Enter the array of elements for matrix\n");
				Ring* ring_inf;
				void* elements_array;
				switch(opt){
					case 1:{
						ring_inf = int_ring;
						elements_array = int_array_input(n_rows, n_cols);
						break;
					}
					case 2:{
						ring_inf = complex_ring;
						elements_array = complex_array_input(n_rows, n_cols);
						break;
					}
				}
				Matrix* new_m =  create_matrix_from_array(n_rows, n_cols, elements_array, n_rows*n_cols, ring_inf);
				matrixes_array[len_m_array-1] = new_m;
				system("clear");
				printf("Matrix was successfully created! The matrix number is %d\n", len_m_array);
				break;
			}
			case 2:{
				if(len_m_array == 0){
					printf("The number of entered matrixes is too small. You need al least one matrix\n");
				}
				else{
					system("clear");
					printf("Enter the number of matrix\n");
					int m_number;
					scanf("%d", &m_number);
					if(m_number > len_m_array || m_number < 1){
						clean_mem(&int_ring, &complex_ring, &matrixes_array, len_m_array);
						raise_error(PERMITED_OPERATION, "You entered bad value");
					}
					transpose_matrix(matrixes_array[m_number-1]);
					system("clear");
					printf("The result is:\n");
					print_matrix(matrixes_array[m_number-1]);
					printf("\n");
				}
				break;
			}
			case 3:{
				if(len_m_array < 2){
					printf("The number of entered matrixes is too small. You need al least two matrixes\n");
				}
				else{
					system("clear");
					printf("Enter two matrixes numbers\n");
					int n1, n2;
					int check_ind = scanf("%d%d", &n1, &n2);
					if(check_ind != 2 || n1 > len_m_array || n2 > len_m_array|| n1 < 1 || n2 < 1){
						clean_mem(&int_ring, &complex_ring, &matrixes_array, len_m_array);
						raise_error(PERMITED_OPERATION, "You entered bad value");
					}
					Matrix* result = sum_matrix(matrixes_array[n1-1], matrixes_array[n2-1]);
					len_m_array +=1;
				    matrixes_array = (Matrix**)realloc(matrixes_array, len_m_array*sizeof(Matrix*));
				    matrixes_array[len_m_array-1] = result;
				    system("clear");
				    printf("The result is:\n");
				    print_matrix(result);
				    printf("The result was saved as matrix with number %d\n", len_m_array);
				    printf("\n");
				}
				break;
			}
			case 4:{
				if(len_m_array == 0){
					printf("The number of entered matrixes is too small. You need al least one matrix\n");
				}
				else{
					system("clear");
					printf("Enter matrix number\n");
					int n1;
					int check_ind = scanf("%d", &n1);
					if(check_ind != 1 || n1 > len_m_array || n1 < 1){
						clean_mem(&int_ring, &complex_ring, &matrixes_array, len_m_array);
						raise_error(PERMITED_OPERATION, "You entered bad value");
					}
					void* coef;
					if(matrixes_array[n1-1]->ring_inf == int_ring){
						int number;
						system("clear");
						printf("Enter integer\n");
						int check_vals = scanf("%d", &number);
						if(check_vals != 1){
							clean_mem(&int_ring, &complex_ring, &matrixes_array, len_m_array);
							raise_error(PERMITED_OPERATION, "You entered bad value");
						}
						coef = &number;
					}
					else{
						double re, im;
						system("clear");
						printf("Enter re and im for complex number\n");
						int check_vals = scanf("%lf%lf", &re, &im);
						if(check_vals != 2){
							clean_mem(&int_ring, &complex_ring, &matrixes_array, len_m_array);
							raise_error(PERMITED_OPERATION, "You entered bad value");
						}
						Complex number = create_new_complex(re, im);
						coef = &number;
					}
					Matrix* result = mult_matrix_to_num(matrixes_array[n1-1], coef);
					len_m_array +=1;
				    matrixes_array = (Matrix**)realloc(matrixes_array, len_m_array*sizeof(Matrix*));
				    matrixes_array[len_m_array-1] = result;
				    system("clear");
				    printf("The result is:\n");
				    print_matrix(result);
				    printf("The result was saved as matrix with number %d\n", len_m_array);
				    printf("\n");
				}
				break;
			}
			case 5:{
				if(len_m_array < 2){
					printf("The number of entered matrixes is too small. You need al least two matrixes\n");
				}
				else{
					system("clear");
					printf("Enter two matrixes numbers\n");
					int n1, n2;
					int check_ind = scanf("%d%d", &n1, &n2);
					if(check_ind != 2 || n1 > len_m_array || n2 > len_m_array || n1 < 1 || n2 < 1){
						clean_mem(&int_ring, &complex_ring, &matrixes_array, len_m_array);
						raise_error(PERMITED_OPERATION, "You entered bad value");
					}
					Matrix* result = mult_matrix_to_matrix(matrixes_array[n1-1], matrixes_array[n2-1]);
					len_m_array +=1;
				    matrixes_array = (Matrix**)realloc(matrixes_array, len_m_array*sizeof(Matrix*));
				    matrixes_array[len_m_array-1] = result;
				    system("clear");
				    printf("The result is:\n");
				    print_matrix(result);
				    printf("The result was saved as matrix with number %d\n", len_m_array);
				    printf("\n");
				}
				break;
			}
			case 6:{
				system("clear");
				clean_mem(&int_ring, &complex_ring, &matrixes_array, len_m_array);
				break;
			}
		}
	}
}

