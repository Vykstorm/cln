// float_sign().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"

#include "cl_inline.h"
#include "cl_DF_minusp.cc"

namespace cln {

CL_INLINE2 const cl_DF CL_INLINE2_DECL(float_sign) (const cl_DF& x)
{
// Methode: x>=0 -> Ergebnis 1.0; x<0 -> Ergebnis -1.0
	return (!minusp_inline(x) ? cl_DF_1 : cl_DF_minus1);
}

}  // namespace cln
