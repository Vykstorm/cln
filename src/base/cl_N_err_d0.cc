// cl_error_division_by_0().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_N.h"


// Implementation.

#include "cl_io.h"
#include "cl_abort.h"

void cl_error_division_by_0 (void)
{
	fprint(cl_stderr, "Division by zero.\n");
	cl_abort();
}
