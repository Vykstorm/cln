// float_sign().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"
#include "cl_LF_impl.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_LF_minusp.cc"

namespace cln {

MAYBE_INLINE2
const cl_LF float_sign (const cl_LF& x)
{
// Methode: x>=0 -> Ergebnis 1.0; x<0 -> Ergebnis -1.0
	return encode_LF1s(TheLfloat(x)->sign,TheLfloat(x)->len);
}

}  // namespace cln
