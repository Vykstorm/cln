// cl_notreached_abort().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_macros.h"


// Implementation.

#include "cl_io.h"
#include "cl_abort.h"

void cl_notreached_abort (const char* filename, int lineno)
{
	fprint(cl_stderr, "Internal error: statement in file ");
	fprint(cl_stderr, filename);
	fprint(cl_stderr, ", line ");
	fprintdecimal(cl_stderr, lineno);
	fprint(cl_stderr, " has been reached!!\n");
	fprint(cl_stderr, "Please send the authors of the program a description how you produced this error!\n");
	cl_abort();
}
