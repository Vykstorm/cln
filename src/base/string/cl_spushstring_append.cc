// class cl_spushstring.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_spushstring.h"


// Implementation.

#include <string.h> // declares memcpy()

void cl_spushstring::append (const char * ptr, uintL len)
{
	if (index + len > alloc) {
		var uintL newalloc = index+2*len;
		if (newalloc < 2*alloc) { newalloc = 2*alloc; }
		var char* newbuffer = (char *) cl_malloc_hook(newalloc);
		memcpy(newbuffer,buffer,alloc);
		cl_free_hook(buffer);
		buffer = newbuffer;
		alloc = newalloc;
	}
	// Now index+len <= alloc.
	for (uintL count = len; count > 0; count--)
		buffer[index++] = *ptr++;
}
