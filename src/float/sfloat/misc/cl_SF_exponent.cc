// float_exponent().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

#include "cl_SF.h"

MAYBE_INLINE
sintL float_exponent (const cl_SF& x)
{
	var uintL uexp = SF_uexp(x);
	if (uexp==0) { return 0; }
	return (sintL)(uexp - SF_exp_mid);
}
