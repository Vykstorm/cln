// float_exponent().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"

namespace cln {

MAYBE_INLINE
sintL float_exponent (const cl_LF& x)
{
	var uintL uexp = TheLfloat(x)->expo;
	if (uexp==0) { return 0; }
	return (sintL)(uexp - LF_exp_mid);
}

}  // namespace cln
