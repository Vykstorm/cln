// fprint().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_string.h"


// Implementation.

#include "cl_io.h"

void fprint (cl_ostream stream, const cl_string& str)
{
#if defined(CL_IO_STDIO)
	var const char * ptr = str.asciz();
	var unsigned long i = str.length();
	while (i > 0) {
		fprintchar(stream,*ptr);
		ptr++; i--;
	}
#endif
#if defined(CL_IO_IOSTREAM)
	stream.write(str.asciz(),str.length());
#endif
}
