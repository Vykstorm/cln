// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

#include "cl_inline.h"
#include "cl_SF_zerop.cc"
#include "cl_FF_zerop.cc"
#include "cl_DF_zerop.cc"
#include "cl_LF_zerop.cc"

namespace cln {

bool CL_FLATTEN zerop (const cl_F& x)
{
	floatcase(x
	,	return zerop_inline(x);
	,	return zerop_inline(x);
	,	return zerop_inline(x);
	,	return zerop_inline(x);
	);
}

}  // namespace cln
