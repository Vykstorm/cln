// fceiling().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_minusp.cc"

namespace cln {

const cl_SF fceiling (const cl_SF& x)
{
	if (minusp(x))
		return ftruncate(x);
	else
		return futruncate(x);
}

}  // namespace cln
