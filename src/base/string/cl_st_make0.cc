// cl_make_heap_string().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_string.h"


// Implementation.

#include "cl_malloc.h"
#include "cl_offsetof.h"

MAYBE_INLINE
cl_heap_string* cl_make_heap_string (unsigned long len)
{
	var cl_heap_string* str = (cl_heap_string*) cl_malloc_hook(offsetofa(cl_heap_string,data)+sizeof(char)*(len+1));
	str->refcount = 1;
	str->type = &cl_class_string;
	str->length = len;
	return str;	/* Have to fill data[0..len] yourself. */
}
