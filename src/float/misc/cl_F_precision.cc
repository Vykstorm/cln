// float_precision().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

#include "cl_inline2.h"
#include "cl_SF_precision.cc"
#include "cl_FF_precision.cc"
#include "cl_DF_precision.cc"
#include "cl_LF_precision.cc"

namespace cln {

uintC CL_FLATTEN float_precision (const cl_F& x)
{
	floatcase(x
	,	return float_precision(x);
	,	return float_precision(x);
	,	return float_precision(x);
	,	return float_precision(x);
	);
}

}  // namespace cln
