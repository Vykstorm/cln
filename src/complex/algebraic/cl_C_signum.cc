// signum().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/complex.h"


// Implementation.

#include "cl_C.h"
#include "cln/real.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_C_abs_aux.cc"

namespace cln {

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

}  // namespace cln
