// numerator().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/rational.h"


// Implementation.

#define numerator inline_numerator
#include "cl_RA.h"
#undef numerator

namespace cln {

const cl_I numerator (const cl_RA& r)
{
	return inline_numerator(r);
}

}  // namespace cln
