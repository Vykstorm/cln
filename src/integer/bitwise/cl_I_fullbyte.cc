// cl_fullbyte().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I_byte.h"


// Implementation.

#include "cln/integer.h"
#include "cl_I.h"

namespace cln {

const cl_I cl_fullbyte (uintC p, uintC q)
{
	if (p==q)
		return 0;
	else
		return ash(-1,(cl_I)(unsigned long)p) + ash(1,(cl_I)(unsigned long)q);
}

}  // namespace cln
