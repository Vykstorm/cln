// cl_error_floating_point_overflow().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F.h"


// Implementation.

#include "cln/io.h"
#include "cln/abort.h"

namespace cln {

void cl_error_floating_point_overflow (void)
{
	fprint(std::cerr, "Floating point overflow.\n");
	cl_abort();
}

}  // namespace cln
