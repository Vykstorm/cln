// cl_ln2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F_tran.h"


// Implementation.

#include "cl_F.h"

const cl_F cl_ln2 (cl_float_format_t f)
{
	floatformatcase((uintL)f
	,	return cl_SF_ln2;
	,	return cl_FF_ln2;
	,	return cl_DF_ln2;
	,	return cl_ln2(len);
	);
}
