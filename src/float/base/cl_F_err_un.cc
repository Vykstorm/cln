// cl_error_floating_point_underflow().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F.h"


// Implementation.

#include "cln/io.h"
#include "cln/abort.h"

namespace cln {

void cl_error_floating_point_underflow (void)
{
	fprint(stderr, "Floating point underflow.\n");
	cl_abort();
}

}  // namespace cln
