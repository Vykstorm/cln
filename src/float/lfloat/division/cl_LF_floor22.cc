// floor2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat.h"


// Implementation.

#include "cl_LF.h"

const cl_LF_div_t floor2 (const cl_LF& x, const cl_LF& y)
{
// Methode:
// (q,r) := floor(x/y). Liefere q und x-y*q = y*r.
	var cl_LF_div_t q_r = floor2(x/y);
	var cl_I& q = q_r.quotient;
	var cl_LF& r = q_r.remainder;
	return cl_LF_div_t(q,y*r);
}
