// exp1().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F_tran.h"
#include "cl_F.h"
#include "cl_LF.h"

namespace cln {

const cl_F exp1 (const cl_F& y)
{
	floattypecase(y
	,	return cl_SF_exp1();
	,	return cl_FF_exp1();
	,	return cl_DF_exp1();
	,	return exp1(TheLfloat(y)->len);
	);
}

}  // namespace cln
