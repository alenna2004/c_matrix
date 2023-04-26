#include <stdio.h>
#include <stdlib.h>
#include "intinfo.h"
#include "ring.h"

int INT_ZERO = 0;
int INT_ONE = 1;


void* _int_sum(void* num1, void* num2)
{
	int* ptr_num1 = (int*)num1;
	int* ptr_num2 = (int*)num2;
	int* res = malloc(sizeof(int));
	*res = *ptr_num1 + *ptr_num2;
	return (void*)res;
}


void* _int_mult(void* num1, void* num2)
{
	int* ptr_num1 = (int*)num1;
	int* ptr_num2 = (int*)num2;
	int* res = malloc(sizeof(int));
	*res = (*ptr_num1) * (*ptr_num2);
	return (void*)res;
}


void* _int_minus(void* num)
{
	int* ptr_num = (int*)num;
	int* res = malloc(sizeof(int));
	*res = (*ptr_num)*(-1);
	return (void*)res;
}

void* print_int(void* num)
{
	int* ptr_num = (int*)num;
	printf("%d", *ptr_num);
}


Ring *get_int_ring(void)
{
	Ring* int_ring = _create_ring(sizeof(int), &_int_sum, &INT_ZERO, 
		&_int_minus, &_int_mult, &INT_ONE, &print_int);
	return int_ring;
}

