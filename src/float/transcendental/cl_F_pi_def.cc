// cl_pi().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"
#include "cl_F_tran.h"

const cl_F cl_pi (void)
{
	floatformatcase(cl_default_float_format
	,	return cl_SF_pi;
	,	return cl_FF_pi;
	,	return cl_DF_pi;
	,	return cl_pi(len);
	);
}
