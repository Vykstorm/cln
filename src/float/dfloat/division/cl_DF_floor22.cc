// floor2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_dfloat.h"


// Implementation.

#include "cl_DF.h"

const cl_DF_div_t floor2 (const cl_DF& x, const cl_DF& y)
{
// Methode:
// (q,r) := floor(x/y). Liefere q und x-y*q = y*r.
	var cl_DF_div_t q_r = floor2(x/y);
	var cl_I& q = q_r.quotient;
	var cl_DF& r = q_r.remainder;
	return cl_DF_div_t(q,y*r);
}
