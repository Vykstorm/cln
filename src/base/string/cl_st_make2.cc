// cl_make_heap_string().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_string.h"


// Implementation.

#include "cl_malloc.h"
#include "cl_offsetof.h"

cl_heap_string* cl_make_heap_string (const char * ptr, unsigned long len)
{
	var cl_heap_string* str = (cl_heap_string*) cl_malloc_hook(offsetofa(cl_heap_string,data)+sizeof(char)*(len+1));
	str->refcount = 1;
	str->type = &cl_class_string;
	str->length = len;
	{
		var const char* ptr1 = ptr;
		var char* ptr2 = &str->data[0];
		var uintL count;
		for (count = len; count > 0; count--)
			*ptr2++ = *ptr1++;
		*ptr2++ = '\0';
	}
	return str;
}
