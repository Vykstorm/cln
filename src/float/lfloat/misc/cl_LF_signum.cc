// signum().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"
#include "cl_LF_impl.h"

#include "cl_inline.h"
#include "cl_LF_minusp.cc"
#include "cl_LF_zerop.cc"

namespace cln {

CL_INLINE2 const cl_LF CL_INLINE2_DECL(signum) (const cl_LF& x)
{
	if (zerop_inline(x)) { return x; } // x=0 -> 0.0
	else // je nach Vorzeichen von x
	{ return encode_LF1s(TheLfloat(x)->sign,TheLfloat(x)->len); }
}

}  // namespace cln
