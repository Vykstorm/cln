// cl_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"
#include "cl_SF.h"
#include "cl_FF.h"
#include "cl_DF.h"
#include "cl_LF.h"

const cl_F cl_float (const cl_RA& x)
{
	floatformatcase(cl_default_float_format
	,	return cl_RA_to_SF(x);
	,	return cl_RA_to_FF(x);
	,	return cl_RA_to_DF(x);
	,	return cl_RA_to_LF(x,len);
	);
}
