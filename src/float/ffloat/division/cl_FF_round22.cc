// round2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_ffloat.h"


// Implementation.

#include "cl_FF.h"

const cl_FF_div_t round2 (const cl_FF& x, const cl_FF& y)
{
// Methode:
// (q,r) := round(x/y). Liefere q und x-y*q = y*r.
	var cl_FF_div_t q_r = round2(x/y);
	var cl_I& q = q_r.quotient;
	var cl_FF& r = q_r.remainder;
	return cl_FF_div_t(q,y*r);
}
