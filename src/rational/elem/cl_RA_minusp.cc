// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/rational.h"


// Implementation.

#define minusp inline_minusp
#include "cl_RA.h"
#undef minusp

namespace cln {

cl_boolean minusp (const cl_RA& x)
{
	return inline_minusp(x);
}

}  // namespace cln
