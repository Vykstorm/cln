// ffloor().

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

const cl_DF ffloor (const cl_DF& x)
{
	if (minusp(x))
		return futruncate(x);
	else
		return ftruncate(x);
}

}  // namespace cln
