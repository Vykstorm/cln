// ffloor().

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

const cl_FF ffloor (const cl_FF& x)
{
	if (minusp(x))
		return futruncate(x);
	else
		return ftruncate(x);
}

}  // namespace cln
