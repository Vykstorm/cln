// plusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

#include "cl_inline2.h"
#include "cl_SF_plusp.cc"
#include "cl_FF_plusp.cc"
#include "cl_DF_plusp.cc"
#include "cl_LF_plusp.cc"

namespace cln {

bool CL_FLATTEN plusp (const cl_F& x)
{
	floatcase(x
	,	return plusp_inline(x);
	,	return plusp_inline(x);
	,	return plusp_inline(x);
	,	return plusp_inline(x);
	);
}

}  // namespace cln
