// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_dfloat.h"


// Implementation.

#include "cl_DF.h"

MAYBE_INLINE
cl_boolean minusp (const cl_DF& x)
{
#if (cl_word_size==64)
	return (cl_boolean) ((sint64)TheDfloat(x)->dfloat_value_semhi < 0);
#else
	return (cl_boolean) ((sint32)TheDfloat(x)->dfloat_value_semhi < 0);
#endif
}
