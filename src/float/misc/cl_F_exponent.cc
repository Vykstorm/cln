// float_exponent().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_exponent.cc"
#include "cl_FF_exponent.cc"
#include "cl_DF_exponent.cc"
#include "cl_LF_exponent.cc"

namespace cln {

sintE float_exponent (const cl_F& x)
{
	floatcase(x
	,	return float_exponent(x);
	,	return float_exponent(x);
	,	return float_exponent(x);
	,	return float_exponent(x);
	);
}

}  // namespace cln
