// cl_ln10().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F_tran.h"


// Implementation.

#include "cl_F.h"

namespace cln {

const cl_F cl_ln10 (float_format_t f)
{
	floatformatcase((uintL)f
	,	return cl_SF_ln10;
	,	return cl_FF_ln10;
	,	return cl_DF_ln10;
	,	return cl_ln10(len);
	);
}

}  // namespace cln
