// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#define zerop inline_zerop
#include "cl_I.h"
#undef zerop

namespace cln {

bool zerop (const cl_I& x)
{
	return inline_zerop(x);
}

}  // namespace cln
