// float_exponent().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_dfloat.h"


// Implementation.

#include "cl_DF.h"

MAYBE_INLINE
sintL float_exponent (const cl_DF& x)
{
	var uintL uexp = DF_uexp(TheDfloat(x)->dfloat_value_semhi);
	if (uexp==0) { return 0; }
	return (sintL)(uexp - DF_exp_mid);
}
