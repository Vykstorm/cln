// fprinthexadecimal().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_io.h"


// Implementation.

#if defined(CL_IO_STDIO)

void fprinthexadecimal (cl_ostream stream, unsigned long x)
{
	fprintf(stream,"%lX",x);
}

#endif

#if defined(CL_IO_IOSTREAM)

void fprinthexadecimal (cl_ostream stream, unsigned long x)
{
	#define bufsize 16
	var char buf[bufsize+1];
	var char* bufptr = &buf[bufsize];
	*bufptr = '\0';
	do {
		unsigned long q = x / 16;
		unsigned long r = x % 16;
		*--bufptr = (r<10 ? '0'+r : 'A'-10+r);
		x = q;
	} while (x > 0);
	fprint(stream,bufptr);
	#undef bufsize
}

#endif

void fprinthexadecimal (cl_ostream stream, long x)
{
	if (x >= 0)
		fprintdecimal(stream,(unsigned long)x);
	else {
		fprintchar(stream,'-');
		fprintdecimal(stream,(unsigned long)(-1-x)+1);
	}
}
