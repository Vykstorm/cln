// plusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/rational.h"


// Implementation.

#define minusp inline_minusp
#define zerop inline_zerop
#include "cl_RA.h"
#undef zerop
#undef minusp

namespace cln {

cl_boolean plusp (const cl_RA& x)
{
	if (inline_minusp(x))
		return cl_false; // x<0 -> nein
	elif (inline_zerop(x))
		return cl_false; // x=0 -> nein
	else
		return cl_true; // sonst ist x>0.
}

}  // namespace cln
