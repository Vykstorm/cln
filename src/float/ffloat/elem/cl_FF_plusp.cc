// plusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/ffloat.h"


// Implementation.

#include "cl_FF.h"

#include "cl_inline.h"
#include "cl_FF_minusp.cc"
#include "cl_FF_zerop.cc"

namespace cln {

CL_INLINE2 bool CL_INLINE2_DECL(plusp) (const cl_FF& x)
{
	if (minusp_inline(x))
		return false; // x<0 -> nein
	elif (zerop_inline(x))
		return false; // x=0 -> nein
	else
		return true; // sonst ist x>0.
}

}  // namespace cln
