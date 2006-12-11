// float_exponent().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/ffloat.h"


// Implementation.

#include "cl_FF.h"

namespace cln {

MAYBE_INLINE
sintE float_exponent (const cl_FF& x)
{
	var uintL uexp = FF_uexp(cl_ffloat_value(x));
	if (uexp==0) { return 0; }
	return (sintL)(uexp - FF_exp_mid);
}

}  // namespace cln
