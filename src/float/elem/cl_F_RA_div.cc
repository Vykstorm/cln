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

const cl_F operator/ (const cl_F& x, const cl_RA& y)
{
	floatcase(x
	, /* SF */	if (integerp(y)) {
				DeclareType(cl_I,y);
				return x / cl_I_to_SF(y);
			} else
				return x / cl_RA_to_SF(y);
	, /* FF */	if (integerp(y)) {
				DeclareType(cl_I,y);
				return x / cl_I_to_FF(y);
			} else
				return x / cl_RA_to_FF(y);
	, /* DF */	if (integerp(y)) {
				DeclareType(cl_I,y);
				return x / cl_I_to_DF(y);
			} else
				return x / cl_RA_to_DF(y);
	, /* LF */	if (integerp(y)) {
				DeclareType(cl_I,y);
				return cl_LF_I_div(x,y);
			} else
				return cl_LF_RA_div(x,y);
	);
}
