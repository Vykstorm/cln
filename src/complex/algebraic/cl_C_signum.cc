// signum().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_C_abs_aux.cc"

const cl_N signum (const cl_N& x)
{
// Methode:
// x reell -> klar.
// x komplex -> falls (zerop x), x als Ergebnis, sonst (/ x (abs x)).
	if (realp(x)) {
		DeclareType(cl_R,x);
		return signum(x);
	} else {
		DeclareType(cl_C,x);
		if (zerop(x))
			return x;
		else
			return x / abs(x);
	}
}
