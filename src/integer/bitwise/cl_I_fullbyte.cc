// cl_fullbyte().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I_byte.h"


// Implementation.

#include "cln/integer.h"
#include "cl_I.h"

namespace cln {

const cl_I cl_fullbyte (uintL p, uintL q)
{
	if (p==q)
		return 0;
	else
		return ash(-1,UL_to_I(p)) + ash(1,UL_to_I(q));
}

}  // namespace cln
