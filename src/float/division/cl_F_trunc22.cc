// truncate2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"

const cl_F_div_t truncate2 (const cl_F& x, const cl_F& y)
{
// Methode:
// (q,r) := truncate(x/y). Liefere q und x-y*q = y*r.
	var cl_F_div_t q_r = truncate2(x/y);
	var cl_I& q = q_r.quotient;
	var cl_F& r = q_r.remainder;
	return cl_F_div_t(q,y*r);
}
