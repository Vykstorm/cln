// signum().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat.h"


// Implementation.

#include "cl_LF.h"
#include "cl_LF_impl.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_LF_minusp.cc"
#include "cl_LF_zerop.cc"

MAYBE_INLINE2
const cl_LF signum (const cl_LF& x)
{
	if (zerop(x)) { return x; } // x=0 -> 0.0
	else // je nach Vorzeichen von x
	{ return encode_LF1s(TheLfloat(x)->sign,TheLfloat(x)->len); }
}
