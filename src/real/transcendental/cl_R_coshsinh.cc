// cl_cosh_sinh().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_float.h"
#include "cl_R.h"

const cl_cosh_sinh_t cl_cosh_sinh (const cl_R& x)
{
// Methode:
// x rational -> bei x=0 (1,0) als Ergebnis, sonst x in Float umwandeln.
// x Float -> bekannt.

	if (rationalp(x)) {
		DeclareType(cl_RA,x);
		if (zerop(x)) // x=0 -> (1,0) als Ergebnis
			return cl_cosh_sinh_t(1,0);
		return cl_cosh_sinh(cl_float(x)); // sonst in Float umwandeln
	} else {
		DeclareType(cl_F,x);
		return cl_cosh_sinh(x);
	}
}
