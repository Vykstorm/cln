// cl_abort().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/abort.h"


// Implementation.

#include <stdlib.h>

namespace cln {

void cl_abort (void)
{
	exit(1);
}

}  // namespace cln
