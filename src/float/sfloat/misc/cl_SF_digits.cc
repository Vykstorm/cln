// float_digits().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"

namespace cln {

MAYBE_INLINE
uintL float_digits (const cl_SF& x)
{
	unused x;
	return SF_mant_len+1; // 17
}

}  // namespace cln
