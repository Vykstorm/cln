// signum().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

/* Use inline versions of signum(cl_{SF,FF,DF,LF}) functions */
#include "cl_inline2.h"
#include "cl_SF_signum.cc"
#include "cl_FF_signum.cc"
#include "cl_DF_signum.cc"
#include "cl_LF_signum.cc"

namespace cln {

const cl_F CL_FLATTEN signum (const cl_F& x)
{
	floatcase(x
	,	return signum_inline(x);
	,	return signum_inline(x);
	,	return signum_inline(x);
	,	return signum_inline(x);
	);
}

}  // namespace cln
