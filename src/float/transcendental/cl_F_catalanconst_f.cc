// cl_catalanconst().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"
#include "cl_F_tran.h"

const cl_F cl_catalanconst (cl_float_format_t f)
{
	floatformatcase((uintL)f
	,	return cl_SF_catalanconst;
	,	return cl_FF_catalanconst;
	,	return cl_DF_catalanconst;
	,	return cl_catalanconst(len);
	);
}
