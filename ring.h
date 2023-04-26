#include <stddef.h>
#ifndef RING_H
#define RING_H


typedef struct Ring
{
	size_t size;
	void* (*sum)(void*, void*);
	void* zero;
	void* (*minus)(void*);
	void* (*mult)(void*, void*);
	void* one;
	void* (*print_el)(void*);
} Ring;


Ring* _create_ring(size_t size, 
	void* (*sum)(void*, void*),
	void* zero, 
	void* (*minus)(void*),
	void* (*mult)(void*, void*),
	void* one,
	void* (*print_el)(void*));

#endif