// exp1().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F_tran.h"
#include "cl_F.h"

namespace cln {

const cl_F exp1 (float_format_t f)
{
	floatformatcase((uintC)f
	,	return cl_SF_exp1();
	,	return cl_FF_exp1();
	,	return cl_DF_exp1();
	,	return exp1(len);
	);
}

}  // namespace cln
