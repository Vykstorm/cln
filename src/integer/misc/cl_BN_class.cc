// cl_class_bignum.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

cl_class cl_class_bignum = {
	NULL,		// empty destructor
	cl_class_flags_subclass_complex | cl_class_flags_subclass_real | cl_class_flags_subclass_rational
};
