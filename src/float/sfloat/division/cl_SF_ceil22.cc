// ceiling2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

#include "cl_SF.h"

const cl_SF_div_t ceiling2 (const cl_SF& x, const cl_SF& y)
{
// Methode:
// (q,r) := ceiling(x/y). Liefere q und x-y*q = y*r.
	var cl_SF_div_t q_r = ceiling2(x/y);
	var cl_I& q = q_r.quotient;
	var cl_SF& r = q_r.remainder;
	return cl_SF_div_t(q,y*r);
}
