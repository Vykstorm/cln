// fceiling().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"

const cl_F fceiling (const cl_R& x, const cl_R& y)
{
// Methode:
// x,y beide rational: ceiling(x,y), Quotienten in Float umwandeln.
// Sonst: fceiling(x/y).
	if (rationalp(x))
		if (rationalp(y)) {
			// beides rationale Zahlen
			DeclareType(cl_RA,x);
			DeclareType(cl_RA,y);
			return cl_float(ceiling1(x,y));
		}
	return fceiling(x/y);
}
