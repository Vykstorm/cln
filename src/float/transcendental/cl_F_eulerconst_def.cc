// cl_eulerconst().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"
#include "cl_F_tran.h"

const cl_F cl_eulerconst (void)
{
	floatformatcase(cl_default_float_format
	,	return cl_SF_eulerconst;
	,	return cl_FF_eulerconst;
	,	return cl_DF_eulerconst;
	,	return cl_eulerconst(len);
	);
}
