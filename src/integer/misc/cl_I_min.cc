// min().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

namespace cln {

const cl_I min (const cl_I& x, const cl_I& y)
{
	return (x <= y ? x : y);
}

}  // namespace cln
