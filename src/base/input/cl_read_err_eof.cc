// read_number_eof().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_number_io.h"


// Implementation.

#include "cl_io.h"
#include "cl_abort.h"

void read_number_eof (void)
{
	fprint(cl_stderr, "read_number: end of stream encountered\n");
	cl_abort();
}
