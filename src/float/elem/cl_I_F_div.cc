// binary operator /

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

const cl_R operator/ (const cl_I& x, const cl_F& y)
{
	if (eq(x,0)) { return 0; }
	floatcase(y
	, /* SF */	return cl_I_to_SF(x) / y;
	, /* FF */	return cl_I_to_FF(x) / y;
	, /* DF */	return cl_I_to_DF(x) / y;
	, /* LF */	return cl_I_to_LF(x,LFlen0(y)) / y; // cf. cl_I_LF_div
	);
}
