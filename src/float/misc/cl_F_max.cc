// max().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

namespace cln {

const cl_F max (const cl_F& x, const cl_F& y)
{
	return (x >= y ? x : y);
}

}  // namespace cln
