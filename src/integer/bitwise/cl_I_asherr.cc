// cl_ash_error().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I_ash.h"


// Implementation.

#include "cl_number.h"
#include "cl_io.h"
#include "cl_integer_io.h"
#include "cl_abort.h"

void cl_ash_error (const cl_I& badamount)
{
	fprint(cl_stderr, "ash: too large shift amount: ");
	fprint(cl_stderr, badamount);
	fprint(cl_stderr, "\n");
	cl_abort();
}
