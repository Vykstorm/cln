// eulerconst().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"
#include "cl_F_tran.h"

namespace cln {

const cl_F eulerconst (float_format_t f)
{
	floatformatcase((uintL)f
	,	return cl_SF_eulerconst;
	,	return cl_FF_eulerconst;
	,	return cl_DF_eulerconst;
	,	return eulerconst(len);
	);
}

}  // namespace cln
