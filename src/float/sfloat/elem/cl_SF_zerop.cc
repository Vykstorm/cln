// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

#include "cl_SF.h"

MAYBE_INLINE
cl_boolean zerop (const cl_SF& x)
{
	return (cl_boolean) (x.word == make_SF_word(0,0,0));
}
