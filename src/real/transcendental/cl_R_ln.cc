// ln().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_float.h"
#include "cl_R.h"

const cl_R ln (const cl_R& x)
{
// Methode:
// x rational -> bei x=1 0 als Ergebnis, sonst x in Float umwandeln.
// x Float -> bekannt.

	if (rationalp(x)) {
		DeclareType(cl_RA,x);
		if (x == 1) // x=1 -> 0 als Ergebnis
			return 0;
		return ln(cl_float(x)); // sonst in Float umwandeln
	} else {
		DeclareType(cl_F,x);
		return ln(x);
	}
}
