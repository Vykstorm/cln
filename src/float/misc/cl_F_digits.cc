// float_digits().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

#include "cl_inline.h"
#include "cl_SF_digits.cc"
#include "cl_FF_digits.cc"
#include "cl_DF_digits.cc"
#include "cl_LF_digits.cc"

namespace cln {

uintC float_digits (const cl_F& x)
{
	floatcase(x
	,	return float_digits_inline(x);
	,	return float_digits_inline(x);
	,	return float_digits_inline(x);
	,	return float_digits_inline(x);
	);
}

}  // namespace cln
