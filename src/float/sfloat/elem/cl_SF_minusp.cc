// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"

namespace cln {

MAYBE_INLINE
cl_boolean minusp (const cl_SF& x)
{
	return (cl_boolean) ((x.word & bit(SF_sign_shift)) != 0);
}

}  // namespace cln
