// read_number_bad_syntax().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_number_io.h"


// Implementation.

#include "cl_io.h"
#include "cl_abort.h"

void read_number_bad_syntax (const char * string, const char * string_limit)
{
	fprint(cl_stderr, "Illegal number syntax: \"");
	for (const char * ptr = string; ptr != string_limit; ptr++)
		fprintchar(cl_stderr, *ptr);
	fprint(cl_stderr, "\"\n");
	cl_abort();
}
