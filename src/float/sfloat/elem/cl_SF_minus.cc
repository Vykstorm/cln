// binary operator -

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_zerop.cc"

namespace cln {

const cl_SF operator- (const cl_SF& x1, const cl_SF& x2)
{
// Methode:
// (- x1 x2) = (+ x1 (- x2))
	if (zerop(x2))
        	return x1;
	else
		return x1 + cl_SF_from_word(x2.word ^ bit(SF_sign_shift));
}

}  // namespace cln
