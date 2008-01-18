// float_sign().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

#include "cl_inline2.h"
#include "cl_SF_sign.cc"
#include "cl_FF_sign.cc"
#include "cl_DF_sign.cc"
#include "cl_LF_sign.cc"

namespace cln {

const cl_F CL_FLATTEN float_sign (const cl_F& x)
{
// Methode: x>=0 -> Ergebnis 1.0; x<0 -> Ergebnis -1.0
	floatcase(x
	,	return float_sign_inline(x);
	,	return float_sign_inline(x);
	,	return float_sign_inline(x);
	,	return float_sign_inline(x);
	);
}

}  // namespace cln
