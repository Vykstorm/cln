// binary operator /

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_RA.h"
#include "cln/sfloat.h"
#include "cln/ffloat.h"
#include "cln/dfloat.h"
#include "cln/lfloat.h"
#include "cl_F.h"
#include "cl_SF.h"
#include "cl_FF.h"
#include "cl_DF.h"
#include "cl_LF.h"

namespace cln {

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

}  // namespace cln
