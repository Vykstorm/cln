// cl_R_to_FF().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cl_R.h"
#include "cl_F.h"
#include "cl_FF.h"

#if 0

namespace cln {

const cl_FF cl_R_to_FF (const cl_R& x)
{
	if (rationalp(x)) {
		DeclareType(cl_RA,x);
		return cl_RA_to_FF(x);
	} else {
		DeclareType(cl_F,x);
		return cl_F_to_FF(x);
	}
}

}  // namespace cln

#else // fully inlined, faster

#include "cl_RA.h"
#include "cl_I.h"

namespace cln {

const cl_FF cl_R_to_FF (const cl_R& x)
{
	realcase6(x
	,	return cl_I_to_FF(x);
	,	return cl_RA_to_FF(x);
	,	return cl_SF_to_FF(x);
	,	return x;
	,	return cl_DF_to_FF(x);
	,	return cl_LF_to_FF(x);
	);
}

}  // namespace cln

#endif
