#include <stdio.h>
#include <stdlib.h>
#include "complex.h"
#include "ring.h"



Complex create_new_complex(double re, double im)
{
	//Complex* new_compl = malloc(sizeof(Complex));
	Complex new_compl;
	new_compl.re = re;
	new_compl.im = im;
	return new_compl;
}


Complex _get_complex_zero()
{
	Complex zero = create_new_complex(0,0);
	return zero;
}


Complex _get_complex_one()
{
	Complex one = create_new_complex(1,1);
	return one;
}


void* _complex_sum(void* num1, void* num2)
{
	Complex* ptr_num1 = (Complex*)num1;
	Complex* ptr_num2 = (Complex*)num2;
	Complex* res = malloc(sizeof(Complex));
	res->re = ptr_num1->re + ptr_num2->re;
	res->im = ptr_num1->im + ptr_num2->im;
	return (void*)res;
}


void* _complex_mult(void* num1, void* num2)
{
	Complex* ptr_num1 = (Complex*)num1;
	Complex* ptr_num2 = (Complex*)num2;
	Complex* res = malloc(sizeof(Complex));
	res->re = (ptr_num1->re) * (ptr_num2->re) - (ptr_num1->im) * (ptr_num2->im);
	res->im = (ptr_num1->re) * (ptr_num2->im) + (ptr_num1->im) * (ptr_num2->re);
	return (void*)res;
}


void* _complex_minus(void* num)
{
	Complex* ptr_num = (Complex*)num;
	Complex* res = malloc(sizeof(Complex));
	res->re = (ptr_num->re)*(-1);
	res->im = (ptr_num->im)*(-1);
	return (void*)res;
}


void* print_compl(void* num)
{
	Complex* ptr_num = (Complex*)num;
	printf("%lf + %lfi", ptr_num->re, ptr_num->im);
}


Ring *get_complex_ring(void)
{
	Complex compl_zero = _get_complex_zero();
	Complex compl_one = _get_complex_one();
	Ring* complex_ring = _create_ring(sizeof(Complex), &_complex_sum, &compl_zero, 
		&_complex_minus, &_complex_mult, &compl_one, &print_compl);
	return complex_ring;
}

