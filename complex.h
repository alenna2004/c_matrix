#include "ring.h"
#ifndef COMPLEX_H
#define COMPLEX_H


typedef struct Complex
{
	double re;
	double im;
} Complex;


Ring *get_complex_ring(void);
Complex create_new_complex(double re, double im);


#endif