// integer_decode_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_idecode.cc"
#include "cl_FF_idecode.cc"
#include "cl_DF_idecode.cc"
#include "cl_LF_idecode.cc"

const cl_idecoded_float integer_decode_float (const cl_F& x)
{
	floatcase(x
	,	return integer_decode_float(x);
	,	return integer_decode_float(x);
	,	return integer_decode_float(x);
	,	return integer_decode_float(x);
	);
}
