// cl_notify_composite().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_MI.h"


// Implementation.

#include "cl_io.h"
#include "cl_abort.h"

cl_composite_condition* cl_notify_composite (const cl_modint_ring& R, const cl_I& nonunit)
{
	return new cl_composite_condition(R->modulus,gcd(R->modulus,nonunit));
}
