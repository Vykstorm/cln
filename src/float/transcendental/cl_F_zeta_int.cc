// cl_zeta().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"
#include "cl_F_tran.h"
#include "cl_LF.h"

const cl_F cl_zeta (int s, const cl_F& y)
{
	floattypecase(y
	,	return cl_LF_to_SF(cl_zeta(s,LF_minlen));
	,	return cl_LF_to_FF(cl_zeta(s,LF_minlen));
	,	return cl_LF_to_DF(cl_zeta(s,LF_minlen));
	,	return cl_zeta(s,TheLfloat(y)->len);
	);
}
