// cl_abort().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_abort.h"


// Implementation.

#include <stdlib.h>

void cl_abort (void)
{
	exit(1);
}
