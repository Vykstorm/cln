// constructor cl_string (const char * s).

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_string.h"


// Implementation.

extern cl_heap_string* cl_make_heap_string (const char * ptr, unsigned long len);

cl_string::cl_string (const char * ptr, unsigned long len)
{
	pointer = cl_make_heap_string(ptr,len);
}
