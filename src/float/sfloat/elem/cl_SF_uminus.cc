// unary operator -

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

#include "cl_SF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_zerop.cc"

const cl_SF operator- (const cl_SF& x)
{
// Methode:
// Falls x=0.0, fertig. Sonst Vorzeichenbit umdrehen.
	if (zerop(x))
		return SF_0;
	return cl_SF_from_word(x.word ^ ((cl_uint)1 << SF_sign_shift));
}
