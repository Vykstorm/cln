// cl_ring debugging support.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_ring.h"


// Implementation.

#include "cl_io.h"

void cl_ring_element::debug_print () const
{
	fprint(cl_debugout, *this);
	#ifdef CL_IO_IOSTREAM
	cl_debugout << endl; // newline and flush output
	#else
	fprint(cl_debugout, "\n");
	#endif
}

// This dummy links in this module when <cl_ring.h> requires it.
int cl_ring_debug_module;
