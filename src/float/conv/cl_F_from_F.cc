// cl_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"
#include "cl_LF.h"

const cl_F cl_float (const cl_F& x, const cl_F& y)
{
	floattypecase(y
	,	return cl_F_to_SF(x);
	,	return cl_F_to_FF(x);
	,	return cl_F_to_DF(x);
	,	return cl_F_to_LF(x,TheLfloat(y)->len);
	);
}
