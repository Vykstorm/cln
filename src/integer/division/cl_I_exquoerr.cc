// cl_error_exquo().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I.h"


// Implementation.

#include "cl_io.h"
#include "cl_integer_io.h"
#include "cl_abort.h"

void cl_error_exquo (const cl_I& x, const cl_I& y)
{
	fprint(cl_stderr, "Quotient ");
	fprint(cl_stderr, x);
	fprint(cl_stderr, " / ");
	fprint(cl_stderr, y);
	fprint(cl_stderr, " is not an integer.\n");
	cl_abort();
}
