// cl_pi().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"
#include "cl_F_tran.h"
#include "cl_LF.h"

const cl_F cl_pi (const cl_F& y)
{
	floattypecase(y
	,	return cl_SF_pi;
	,	return cl_FF_pi;
	,	return cl_DF_pi;
	,	return cl_pi(TheLfloat(y)->len);
	);
}
