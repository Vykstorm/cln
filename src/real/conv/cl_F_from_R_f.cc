// cl_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cl_R.h"
#include "cln/float.h"
#include "cl_F.h"

namespace cln {

const cl_F cl_float (const cl_R& x, float_format_t f)
{
	floatformatcase((uintL)f
	,	return cl_R_to_SF(x);
	,	return cl_R_to_FF(x);
	,	return cl_R_to_DF(x);
	,	return cl_R_to_LF(x,len);
	);
}

}  // namespace cln
