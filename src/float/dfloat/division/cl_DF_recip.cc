// recip().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"

namespace cln {

const cl_DF recip (const cl_DF& x)
{
	return cl_DF_1 / x;
}

}  // namespace cln
