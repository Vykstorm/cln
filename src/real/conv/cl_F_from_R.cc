// cl_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cl_R.h"

#if 0

namespace cln {

const cl_F cl_float (const cl_R& x, const cl_F& y)
{
	if (rationalp(x)) {
		DeclareType(cl_RA,x);
		return cl_float(x,y);
	} else {
		DeclareType(cl_F,x);
		return cl_float(x,y);
	}
}

}  // namespace cln

#else // less type dispatch overhead

#include "cl_F.h"
#include "cl_LF.h"

namespace cln {

const cl_F cl_float (const cl_R& x, const cl_F& y)
{
	floattypecase(y
	,	return cl_R_to_SF(x);
	,	return cl_R_to_FF(x);
	,	return cl_R_to_DF(x);
	,	return cl_R_to_LF(x,TheLfloat(y)->len);
	);
}

}  // namespace cln

#endif
