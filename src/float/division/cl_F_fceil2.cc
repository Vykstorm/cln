// fceiling2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"
#include "cl_sfloat.h"
#include "cl_ffloat.h"
#include "cl_dfloat.h"
#include "cl_lfloat.h"
#include "cl_LF.h"

const cl_F_fdiv_t fceiling2 (const cl_F& x)
{
#if 0 // 3 type dispatches
	var cl_F q = fceiling(x);
	return cl_F_fdiv_t(q,x-q);
#else // 1 type dispatch
	floatcase(x
	,	var cl_SF q = fceiling(x); return cl_F_fdiv_t(q,x-q);
	,	var cl_FF q = fceiling(x); return cl_F_fdiv_t(q,x-q);
	,	var cl_DF q = fceiling(x); return cl_F_fdiv_t(q,x-q);
	,	var cl_LF q = fceiling(x); return cl_F_fdiv_t(q,LF_LF_minus_LF(x,q));
	);
#endif
}
