// cl_malloc_hook, cl_free_hook.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_malloc.h"


// Implementation.

#include <stdlib.h>
#include "cl_io.h"
#include "cl_abort.h"

#ifndef malloc
  extern "C" void* malloc (size_t size);
#endif
#ifndef free
  extern "C" void free (void* ptr);
#endif

// Just like malloc() but never return NULL pointers.
static void* xmalloc (size_t size)
{
	void* ptr = malloc(size);
	if (ptr)
		return ptr;
	fprint(cl_stderr, "Out of virtual memory.\n");
	cl_abort();
}

void* (*cl_malloc_hook) (size_t size) = xmalloc;
void (*cl_free_hook) (void* ptr)      = free;

