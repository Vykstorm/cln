// cl_F equal_hashcode().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_N.h"
#include "cl_F.h"

#include "cl_inline.h"
#include "cl_SF_eqhashcode.cc"
#include "cl_FF_eqhashcode.cc"
#include "cl_DF_eqhashcode.cc"
#include "cl_LF_eqhashcode.cc"

namespace cln {

uint32 CL_FLATTEN equal_hashcode (const cl_F& x)
{
	floatcase(x
	,	return equal_hashcode_inline(x);
	,	return equal_hashcode_inline(x);
	,	return equal_hashcode_inline(x);
	,	return equal_hashcode_inline(x);
	);
}

}  // namespace cln
