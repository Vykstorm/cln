// fceiling().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_LF_minusp.cc"

namespace cln {

const cl_LF fceiling (const cl_LF& x)
{
	if (minusp(x))
		return ftruncate(x);
	else
		return futruncate(x);
}

}  // namespace cln
