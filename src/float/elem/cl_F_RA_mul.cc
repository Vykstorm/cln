// binary operator *

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_RA.h"
#include "cl_sfloat.h"
#include "cl_ffloat.h"
#include "cl_dfloat.h"
#include "cl_lfloat.h"
#include "cl_F.h"
#include "cl_SF.h"
#include "cl_FF.h"
#include "cl_DF.h"
#include "cl_LF.h"

const cl_R cl_F_RA_mul (const cl_F& x, const cl_RA& y)
{
	if (eq(y,0)) { return 0; } // x * 0 = exakte 0
	floatcase(x
	, /* SF */	return x * cl_RA_to_SF(y);
	, /* FF */	return x * cl_RA_to_FF(y);
	, /* DF */	return x * cl_RA_to_DF(y);
	, /* LF */	return cl_LF_RA_mul(x,y);
	);
}
