// cl_catalanconst().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"
#include "cl_F_tran.h"
#include "cl_LF.h"

const cl_F cl_catalanconst (const cl_F& y)
{
	floattypecase(y
	,	return cl_SF_catalanconst;
	,	return cl_FF_catalanconst;
	,	return cl_DF_catalanconst;
	,	return cl_catalanconst(TheLfloat(y)->len);
	);
}
