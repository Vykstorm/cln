// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

#include "cl_inline.h"
#include "cl_SF_minusp.cc"
#include "cl_FF_minusp.cc"
#include "cl_DF_minusp.cc"
#include "cl_LF_minusp.cc"

namespace cln {

bool CL_FLATTEN minusp (const cl_F& x)
{
	floatcase(x
	,	return minusp_inline(x);
	,	return minusp_inline(x);
	,	return minusp_inline(x);
	,	return minusp_inline(x);
	);
}

}  // namespace cln
