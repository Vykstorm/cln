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

const cl_F cl_float (const cl_I& x, cl_float_format_t f)
{
	floatformatcase((uintL)f
	,	return cl_I_to_SF(x);
	,	return cl_I_to_FF(x);
	,	return cl_I_to_DF(x);
	,	return cl_I_to_LF(x,len);
	);
}
