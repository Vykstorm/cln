// float_exponent().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"

namespace cln {

MAYBE_INLINE
sintE float_exponent (const cl_LF& x)
{
	var uintE uexp = TheLfloat(x)->expo;
	if (uexp==0) { return 0; }
	return (sintE)(uexp - LF_exp_mid);
}

}  // namespace cln
