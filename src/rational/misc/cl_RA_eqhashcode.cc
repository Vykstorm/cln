// cl_RA equal_hashcode().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#include "cl_N.h"
#include "cl_RA.h"

uint32 cl_equal_hashcode (const cl_RA& r)
{
	if (integerp(r)) {
		DeclareType(cl_I,r);
		return cl_equal_hashcode(r);
	} else {
		// Making sure that a float and its rational equivalent have
		// the same hash code is tricky. This code depends on the fact
		// that the equal_hashcode_low macro is linear in `exp'.
		DeclareType(cl_RT,r);
		return cl_equal_hashcode(numerator(r))
		       - cl_equal_hashcode(denominator(r))
		       + equal_hashcode_one;
	}
}
