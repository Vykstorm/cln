// cl_class_lfloat.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat.h"


// Implementation.

cl_class cl_class_lfloat = {
	NULL,		// empty destructor
	cl_class_flags_subclass_complex | cl_class_flags_subclass_real | cl_class_flags_subclass_float
};
