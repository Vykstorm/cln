// ftruncate2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_R_div_t.h"

#if 0 // 2 type dispatches

#include "cl_rational.h"
#include "cl_float.h"
#include "cl_R_div_t.h"

const cl_R_fdiv_t ftruncate2 (const cl_R& x)
{
	if (rationalp(x)) {
		DeclareType(cl_RA,x);
		var cl_RA_div_t q_r = truncate2(x);
		var cl_I& q = q_r.quotient;
		var cl_RA& r = q_r.remainder;
		return cl_R_fdiv_t(cl_float(q),r);
	} else {
		DeclareType(cl_F,x);
		return ftruncate2(x);
	}
}

#else // 1 type dispatch

#include "cl_RA.h"
#include "cl_integer.h"
#include "cl_sfloat.h"
#include "cl_ffloat.h"
#include "cl_dfloat.h"
#include "cl_lfloat.h"
#include "cl_LF.h"

const cl_R_fdiv_t ftruncate2 (const cl_R& x)
{
	realcase6(x
	,	return cl_R_fdiv_t(cl_float(x),0);
	,	var const cl_I& a = numerator(x);
		var const cl_I& b = denominator(x);
		var cl_I_div_t q_r = truncate2(a,b);
		var cl_I& q = q_r.quotient;
		var cl_I& r = q_r.remainder;
		return cl_R_fdiv_t(cl_float(q),I_I_to_RT(r,b));
	,	var cl_SF q = ftruncate(x); return cl_R_fdiv_t(q,x-q);
	,	var cl_FF q = ftruncate(x); return cl_R_fdiv_t(q,x-q);
	,	var cl_DF q = ftruncate(x); return cl_R_fdiv_t(q,x-q);
	,	var cl_LF q = ftruncate(x); return cl_R_fdiv_t(q,LF_LF_minus_LF(x,q));
	);
}

#endif
