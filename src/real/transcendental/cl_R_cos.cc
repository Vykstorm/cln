// cos().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_float.h"
#include "cl_R.h"

const cl_R cos (const cl_R& x)
{
// Methode:
// x rational -> bei x=0 1 als Ergebnis, sonst x in Float umwandeln.
// x Float -> bekannt.

	if (rationalp(x)) {
		DeclareType(cl_RA,x);
		if (zerop(x)) // x=0 -> 1 als Ergebnis
			return 1;
		return cos(cl_float(x)); // sonst in Float umwandeln
	} else {
		DeclareType(cl_F,x);
		return cos(x);
	}
}
