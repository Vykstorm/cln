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

const cl_F operator/ (const cl_F& x, const cl_I& y)
{
	floatcase(x
	, /* SF */	return x / cl_I_to_SF(y);
	, /* FF */	return x / cl_I_to_FF(y);
	, /* DF */	return x / cl_I_to_DF(y);
	, /* LF */	return cl_LF_I_div(x,y);
	);
}

}  // namespace cln
