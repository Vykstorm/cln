// ceiling1().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_rational.h"

const cl_I ceiling1 (const cl_R& x, const cl_R& y)
{
// Methode:
// Beides rationale Zahlen -> ceiling1(x,y).
// Sonst: ceiling1(x/y).
	if (rationalp(x))
		if (rationalp(y)) {
			DeclareType(cl_RA,x);
			DeclareType(cl_RA,y);
			return ceiling1(x,y);
		}
	return ceiling1(x/y);
}
