// signum().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

#undef MAYBE_INLINE2
#define MAYBE_INLINE2 inline
#include "cl_SF_signum.cc"
#include "cl_FF_signum.cc"
#include "cl_DF_signum.cc"
#include "cl_LF_signum.cc"

namespace cln {

const cl_F signum (const cl_F& x)
{
	floatcase(x
	,	return signum(x);
	,	return signum(x);
	,	return signum(x);
	,	return signum(x);
	);
}

}  // namespace cln
