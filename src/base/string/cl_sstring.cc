// cl_sstring().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sstring.h"


// Implementation.

#include "cl_malloc.h"

char * cl_sstring (const char * ptr, uintL len)
{
	var char * string = (char *) cl_malloc_hook(len+1);
	{
		var const char* ptr1 = ptr;
		var char* ptr2 = string;
		var uintL count;
		for (count = len; count > 0; count--)
			*ptr2++ = *ptr1++;
		*ptr2++ = '\0';
	}
	return string;
}
