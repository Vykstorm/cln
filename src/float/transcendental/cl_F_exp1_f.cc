// cl_exp1().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F_tran.h"
#include "cl_F.h"

const cl_F cl_exp1 (cl_float_format_t f)
{
	floatformatcase((uintL)f
	,	return cl_SF_exp1;
	,	return cl_FF_exp1;
	,	return cl_DF_exp1;
	,	return cl_exp1(len);
	);
}
