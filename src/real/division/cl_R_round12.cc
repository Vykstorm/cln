// round1().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_rational.h"

const cl_I round1 (const cl_R& x, const cl_R& y)
{
// Methode:
// Beides rationale Zahlen -> round1(x,y).
// Sonst: round1(x/y).
	if (rationalp(x))
		if (rationalp(y)) {
			DeclareType(cl_RA,x);
			DeclareType(cl_RA,y);
			return round1(x,y);
		}
	return round1(x/y);
}
