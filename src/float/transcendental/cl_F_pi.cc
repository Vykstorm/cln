// pi().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"
#include "cl_F_tran.h"
#include "cl_LF.h"

namespace cln {

const cl_F pi (const cl_F& y)
{
	floattypecase(y
	,	return cl_SF_pi;
	,	return cl_FF_pi;
	,	return cl_DF_pi;
	,	return pi(TheLfloat(y)->len);
	);
}

}  // namespace cln
