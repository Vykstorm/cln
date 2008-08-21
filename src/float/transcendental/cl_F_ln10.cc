// cl_ln10().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F_tran.h"


// Implementation.

#include "cl_F.h"
#include "cl_LF.h"

namespace cln {

const cl_F cl_ln10 (const cl_F& y)
{
	floattypecase(y
	,	return cl_SF_ln10();
	,	return cl_FF_ln10();
	,	return cl_DF_ln10();
	,	return cl_ln10(TheLfloat(y)->len);
	);
}

}  // namespace cln
