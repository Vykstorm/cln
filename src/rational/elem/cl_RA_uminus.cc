// unary operator -

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#include "cl_RA.h"
#include "cl_integer.h"

const cl_RA operator- (const cl_RA& r)
{
// Methode:
// r Integer -> klar.
// r = a/b -> Ergebnis (- a)/b
	if (integerp(r)) {
		DeclareType(cl_I,r);
		return -r;
	} else {
		DeclareType(cl_RT,r);
		var const cl_I& a = numerator(r);
		var const cl_I& b = denominator(r);
		// Immer noch b>1 und ggT(-a,b) = ggT(a,b) = 1
		return I_I_to_RT(-a,b);
	}
}
