// zeta().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"
#include "cl_F_tran.h"
#include "cl_LF.h"

namespace cln {

const cl_F zeta (int s, float_format_t f)
{
	floatformatcase((uintL)f
	,	return cl_LF_to_SF(zeta(s,LF_minlen));
	,	return cl_LF_to_FF(zeta(s,LF_minlen));
	,	return cl_LF_to_DF(zeta(s,LF_minlen));
	,	return zeta(s,len);
	);
}

}  // namespace cln
