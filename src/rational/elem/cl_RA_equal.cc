// cl_equal().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#include "cl_RA.h"
#include "cl_integer.h"

cl_boolean cl_equal (const cl_RA& r, const cl_RA& s)
{
// Methode:
// r,s Integer -> klar
// r Integer, s Ratio: verschieden.
// r Ratio, s Integer: verschieden.
// r,s Ratios: r=a/b, s=c/d. Vergleiche a mit c und b mit d.
	if (integerp(r))
		if (integerp(s)) {
			// r,s beide Integer
			DeclareType(cl_I,r);
			DeclareType(cl_I,s);
			return cl_equal(r,s);
		} else
			// r Integer, s Ratio
			return cl_false;
	else
		if (integerp(s))
			// r Ratio, s Integer
			return cl_false;
		else {
			DeclareType(cl_RT,r);
			DeclareType(cl_RT,s);
			// r,s Ratios
			if (!cl_equal(numerator(r),numerator(s)))
				return cl_false;
			if (!cl_equal(denominator(r),denominator(s)))
				return cl_false;
			return cl_true;
		}
}
