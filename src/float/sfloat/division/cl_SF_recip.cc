// recip().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"

namespace cln {

const cl_SF recip (const cl_SF& x)
{
	return SF_1 / x;
}

}  // namespace cln
