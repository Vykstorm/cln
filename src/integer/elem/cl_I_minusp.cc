// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#define minusp inline_minusp
#include "cl_I.h"
#undef minusp

namespace cln {

cl_boolean minusp (const cl_I& x)
{
	return inline_minusp(x);
}

}  // namespace cln
