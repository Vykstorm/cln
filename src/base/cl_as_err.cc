// cl_as_error().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_N.h"


// Implementation.

#include "cl_io.h"
#include "cl_abort.h"

void cl_as_error (const cl_number& obj, const char * typestring, const char * filename, int line)
{
	fprint(cl_stderr, "Type assertion failed: in file ");
	fprint(cl_stderr, filename);
	fprint(cl_stderr, ", line ");
	fprintdecimal(cl_stderr, line);
	fprint(cl_stderr, ", not ");
	fprint(cl_stderr, typestring);
	fprint(cl_stderr, ": ");
#if 0 // This brings in a dependency from the complex and float printer and all the float stuff.
	fprint(cl_stderr, obj);
#else
	fprint(cl_stderr, "@0x");
	fprinthexadecimal(cl_stderr, (unsigned long)(void*)&obj);
	fprint(cl_stderr, ": 0x");
	fprinthexadecimal(cl_stderr, (unsigned long)obj.word);
#endif
	fprint(cl_stderr, "\n");
	cl_abort();
}
