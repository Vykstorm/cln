// destructor ~cl_timing().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_timing.h"


// Implementation.

cl_timing::~cl_timing ()
{
	report_fn(*this);
}
