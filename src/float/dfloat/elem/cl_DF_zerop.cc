// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"

namespace cln {

MAYBE_INLINE
cl_boolean zerop (const cl_DF& x)
{
#if 0
	return (cl_boolean) (DF_uexp(TheDfloat(x)->dfloat_value_semhi) == 0);
#else // this is faster
	return (cl_boolean) (TheDfloat(x)->dfloat_value_semhi == 0);
#endif
}

}  // namespace cln
