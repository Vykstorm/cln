// plus1().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#include "cl_RA.h"
#include "cl_integer.h"

const cl_RA plus1 (const cl_RA& r)
{
// Methode:
// Falls r ein Integer ist: I_1_plus_I anwenden
// Falls r = a/b: (a+b)/b, wobei b>1 und ggT(a+b,b)=ggT(a,b)=1 ist.
	if (integerp(r)) {
		DeclareType(cl_I,r);
		return plus1(r);
	} else {
		DeclareType(cl_RT,r);
		var const cl_I& a = numerator(r);
		var const cl_I& b = denominator(r);
		return I_I_to_RT(a+b,b);
	}
}
