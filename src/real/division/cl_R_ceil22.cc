// ceiling2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_rational.h"
#include "cl_R_div_t.h"

const cl_R_div_t ceiling2 (const cl_R& x, const cl_R& y)
{
// Methode:
// Beides rationale Zahlen -> ceiling2(x,y).
// Sonst: ceiling2(x/y) -> (q,r). Liefere q und x-y*q=y*r.
	if (rationalp(x))
		if (rationalp(y)) {
			DeclareType(cl_RA,x);
			DeclareType(cl_RA,y);
			return ceiling2(x,y);
		}
	var cl_R_div_t q_r = ceiling2(x/y);
	var cl_I& q = q_r.quotient;
	var cl_R& r = q_r.remainder;
	return cl_R_div_t(q,y*r);
}
