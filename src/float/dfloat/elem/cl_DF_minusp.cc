// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"

namespace cln {

MAYBE_INLINE
bool minusp (const cl_DF& x)
{
#if (cl_word_size==64)
	return (sint64)TheDfloat(x)->dfloat_value_semhi < 0;
#else
	return (sint32)TheDfloat(x)->dfloat_value_semhi < 0;
#endif
}

}  // namespace cln
