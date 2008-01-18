// plusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"

/* For inline versions of minusp and zerop */
#include "cl_inline.h"
#include "cl_SF_minusp.cc"
#include "cl_SF_zerop.cc"

namespace cln {

CL_INLINE2 bool CL_INLINE2_DECL(plusp) (const cl_SF& x)
{
	if (minusp_inline(x))
		return false; // x<0 -> nein
	elif (zerop_inline(x))
		return false; // x=0 -> nein
	else
		return true; // sonst ist x>0.
}

}  // namespace cln
