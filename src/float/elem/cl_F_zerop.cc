// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_zerop.cc"
#include "cl_FF_zerop.cc"
#include "cl_DF_zerop.cc"
#include "cl_LF_zerop.cc"

namespace cln {

cl_boolean zerop (const cl_F& x)
{
	floatcase(x
	,	return zerop(x);
	,	return zerop(x);
	,	return zerop(x);
	,	return zerop(x);
	);
}

}  // namespace cln
