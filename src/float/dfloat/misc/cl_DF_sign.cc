// float_sign().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_DF_minusp.cc"

namespace cln {

MAYBE_INLINE2
const cl_DF float_sign (const cl_DF& x)
{
// Methode: x>=0 -> Ergebnis 1.0; x<0 -> Ergebnis -1.0
	return (!minusp(x) ? cl_DF_1 : cl_DF_minus1);
}

}  // namespace cln
