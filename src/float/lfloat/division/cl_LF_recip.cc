// recip().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat.h"


// Implementation.

#include "cl_LF.h"
#include "cl_LF_impl.h"

ALL_cl_LF_OPERATIONS_SAME_PRECISION()

const cl_LF recip (const cl_LF& x)
{
	return encode_LF1(TheLfloat(x)->len) / x;
}
