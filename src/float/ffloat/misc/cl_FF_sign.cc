// float_sign().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/ffloat.h"


// Implementation.

#include "cl_FF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_FF_minusp.cc"

namespace cln {

MAYBE_INLINE2
const cl_FF float_sign (const cl_FF& x)
{
// Methode: x>=0 -> Ergebnis 1.0; x<0 -> Ergebnis -1.0
	return (!minusp(x) ? cl_FF_1 : cl_FF_minus1);
}

}  // namespace cln
