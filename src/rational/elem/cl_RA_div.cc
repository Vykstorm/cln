// binary operator /

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#include "cl_RA.h"
#include "cl_integer.h"

const cl_RA operator/ (const cl_RA& r, const cl_RA& s)
{
// Methode:
// (* r (/ s))
	if (integerp(r) && integerp(s)) {
		DeclareType(cl_I,r);
		DeclareType(cl_I,s);
		// r und s Integers -> schnell abhandeln
		return I_I_div_RA(r,s);
	}
	return r * recip(s);
}
