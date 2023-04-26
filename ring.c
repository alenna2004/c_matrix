#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "ring.h"


Ring* _create_ring(size_t size, 
	void* (*sum)(void*, void*),
	void* zero, 
	void* (*minus)(void*),
	void* (*mult)(void*, void*),
	void* one,
	void* (*print_el)(void*))
{
	Ring* new_ring = malloc(sizeof(Ring));
	new_ring->size = size;
	new_ring->sum = sum;
	new_ring->zero = zero;
	new_ring->minus = minus;
	new_ring->mult = mult;
	new_ring->one = one;
	new_ring->print_el = print_el;
	return new_ring;
}

