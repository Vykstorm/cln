// cl_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"
#include "cl_SF.h"
#include "cl_FF.h"
#include "cl_DF.h"
#include "cl_LF.h"

namespace cln {

const cl_F cl_float (const cl_I& x, const cl_F& y)
{
	floattypecase(y
	,	return cl_I_to_SF(x);
	,	return cl_I_to_FF(x);
	,	return cl_I_to_DF(x);
	,	return cl_I_to_LF(x,TheLfloat(y)->len);
	);
}

}  // namespace cln
