// cl_alloc_alloca_header(), cl_free_alloca_header().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_alloca.h"


// Implementation.

#include "cl_malloc.h"
#include "cl_offsetof.h"

cl_alloca_header* cl_alloc_alloca_header (size_t size)
{
	var cl_alloca_header* pointer =
	  (cl_alloca_header*)cl_malloc_hook(size+offsetofa(cl_alloca_header,usable_memory));
	pointer->next = NULL;
	return pointer;
}

void cl_free_alloca_header (cl_alloca_header* pointer)
{
	do {
		cl_alloca_header* next = pointer->next;
		cl_free_hook(pointer);
		pointer = next;
	} while (pointer != NULL);
}
