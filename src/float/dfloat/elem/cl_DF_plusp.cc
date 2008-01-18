// plusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"

#include "cl_inline.h"
#include "cl_DF_minusp.cc"
#include "cl_DF_zerop.cc"

namespace cln {

CL_INLINE2 bool CL_INLINE2_DECL(plusp) (const cl_DF& x)
{
	if (minusp_inline(x))
		return false; // x<0 -> nein
	elif (zerop_inline(x))
		return false; // x=0 -> nein
	else
		return true; // sonst ist x>0.
}

}  // namespace cln
