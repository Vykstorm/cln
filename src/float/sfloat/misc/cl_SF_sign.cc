// float_sign().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

#include "cl_SF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_minusp.cc"

MAYBE_INLINE2
const cl_SF float_sign (const cl_SF& x)
{
// Methode: x>=0 -> Ergebnis 1.0; x<0 -> Ergebnis -1.0
	return encode_SF(SF_sign(x),1,bit(SF_mant_len));
}
