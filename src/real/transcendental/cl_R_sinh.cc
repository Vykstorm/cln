// sinh().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_float.h"
#include "cl_R.h"

const cl_R sinh (const cl_R& x)
{
// Methode:
// x rational -> bei x=0 0 als Ergebnis, sonst x in Float umwandeln.
// x Float -> bekannt.

	if (rationalp(x)) {
		DeclareType(cl_RA,x);
		if (zerop(x)) // x=0 -> 0 als Ergebnis
			return 0;
		return sinh(cl_float(x)); // sonst in Float umwandeln
	} else {
		DeclareType(cl_F,x);
		return sinh(x);
	}
}
