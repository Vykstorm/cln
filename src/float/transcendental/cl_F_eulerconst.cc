// eulerconst().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"
#include "cl_F_tran.h"
#include "cl_LF.h"

namespace cln {

const cl_F eulerconst (const cl_F& y)
{
	floattypecase(y
	,	return cl_SF_eulerconst();
	,	return cl_FF_eulerconst();
	,	return cl_DF_eulerconst();
	,	return eulerconst(TheLfloat(y)->len);
	);
}

}  // namespace cln
