// cl_eulerconst().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"
#include "cl_F_tran.h"
#include "cl_LF.h"

const cl_F cl_eulerconst (const cl_F& y)
{
	floattypecase(y
	,	return cl_SF_eulerconst;
	,	return cl_FF_eulerconst;
	,	return cl_DF_eulerconst;
	,	return cl_eulerconst(TheLfloat(y)->len);
	);
}
