// cl_error_floating_point_overflow().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F.h"


// Implementation.

#include "cl_io.h"
#include "cl_abort.h"

void cl_error_floating_point_nan (void)
{
	fprint(cl_stderr, "floating point NaN occurred.\n");
	cl_abort();
}
