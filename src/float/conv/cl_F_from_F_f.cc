// cl_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

namespace cln {

const cl_F cl_float (const cl_F& x, float_format_t f)
{
	floatformatcase((uintC)f
	,	return cl_F_to_SF(x);
	,	return cl_F_to_FF(x);
	,	return cl_F_to_DF(x);
	,	return cl_F_to_LF(x,len);
	);
}

}  // namespace cln
