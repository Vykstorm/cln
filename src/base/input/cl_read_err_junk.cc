// read_number_junk().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_number_io.h"


// Implementation.

#include "cl_io.h"
#include "cl_abort.h"

void read_number_junk (const char * string_rest, const char * string, const char * string_limit)
{
	fprint(cl_stderr, "Junk after number: ");
	{ for (const char * ptr = string; ptr != string_rest; ptr++)
		fprintchar(cl_stderr, *ptr);
	}
	fprint(cl_stderr, "\"");
	{ for (const char * ptr = string_rest; ptr != string_limit; ptr++)
		fprintchar(cl_stderr, *ptr);
	}
	fprint(cl_stderr, "\"\n");
	cl_abort();
}
