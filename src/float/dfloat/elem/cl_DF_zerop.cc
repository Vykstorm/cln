// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"

namespace cln {

MAYBE_INLINE
bool zerop (const cl_DF& x)
{
#if 0
	return DF_uexp(TheDfloat(x)->dfloat_value_semhi) == 0;
#else // this is faster
	return TheDfloat(x)->dfloat_value_semhi == 0;
#endif
}

}  // namespace cln
