// recip().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#include "cl_RA.h"
#include "cl_N.h"
#include "cl_I.h"

const cl_RA recip (const cl_RA& r)
{
// Methode:
// r=0 -> Error.
// a:=(numerator r), b:=(denominator r).
// a>0 -> Ergebnis b/a (mit ggT(b,a)=1).
// a<0 -> Ergebnis (- b)/(- a) (mit ggT(-b,-a)=1).
	if (zerop(r))
		cl_error_division_by_0();
	var cl_I a;
	var cl_I b;
	RA_numden_I_I(r, a = , b = );
	if (!minusp(a))
		return I_I_to_RA(b,a);
	else
		// a<0
		return I_I_to_RA(-b,-a);
}
