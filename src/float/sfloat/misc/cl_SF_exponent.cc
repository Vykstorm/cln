// float_exponent().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"

namespace cln {

MAYBE_INLINE
sintE float_exponent (const cl_SF& x)
{
	var uintL uexp = SF_uexp(x);
	if (uexp==0) { return 0; }
	return (sintL)(uexp - SF_exp_mid);
}

}  // namespace cln
