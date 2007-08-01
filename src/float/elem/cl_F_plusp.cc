// plusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

#undef MAYBE_INLINE2
#define MAYBE_INLINE2 inline
#include "cl_SF_plusp.cc"
#include "cl_FF_plusp.cc"
#include "cl_DF_plusp.cc"
#include "cl_LF_plusp.cc"

namespace cln {

bool plusp (const cl_F& x)
{
	floatcase(x
	,	return plusp(x);
	,	return plusp(x);
	,	return plusp(x);
	,	return plusp(x);
	);
}

}  // namespace cln
