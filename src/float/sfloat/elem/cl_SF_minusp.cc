// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

#include "cl_SF.h"

MAYBE_INLINE
cl_boolean minusp (const cl_SF& x)
{
	return (cl_boolean) ((x.word & bit(SF_sign_shift)) != 0);
}
