// class cl_spushstring.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_spushstring.h"


// Implementation.

#include <string.h> // declares memcpy()

void cl_spushstring::push (char c)
{
	if (index >= alloc) {
		var uintL newalloc = 2*alloc;
		var char* newbuffer = (char *) cl_malloc_hook(newalloc);
		memcpy(newbuffer,buffer,alloc);
		cl_free_hook(buffer);
		buffer = newbuffer;
		alloc = newalloc;
	}
	// Now index < alloc.
	buffer[index++] = c;
}
