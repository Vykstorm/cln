// cl_error_floating_point_underflow().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F.h"


// Implementation.

#include "cl_io.h"
#include "cl_abort.h"

void cl_error_floating_point_underflow (void)
{
	fprint(cl_stderr, "Floating point underflow.\n");
	cl_abort();
}
