// float_exponent().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_ffloat.h"


// Implementation.

#include "cl_FF.h"

MAYBE_INLINE
sintL float_exponent (const cl_FF& x)
{
	var uintL uexp = FF_uexp(cl_ffloat_value(x));
	if (uexp==0) { return 0; }
	return (sintL)(uexp - FF_exp_mid);
}
