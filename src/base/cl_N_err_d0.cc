// cl_error_division_by_0().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_N.h"


// Implementation.

#include "cln/io.h"
#include "cln/abort.h"

namespace cln {

void cl_error_division_by_0 (void)
{
	fprint(stderr, "Division by zero.\n");
	cl_abort();
}

}  // namespace cln
