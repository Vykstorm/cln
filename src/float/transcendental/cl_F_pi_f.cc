// pi().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"
#include "cl_F_tran.h"

namespace cln {

const cl_F pi (float_format_t f)
{
	floatformatcase((uintL)f
	,	return cl_SF_pi;
	,	return cl_FF_pi;
	,	return cl_DF_pi;
	,	return pi(len);
	);
}

}  // namespace cln
