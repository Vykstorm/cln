// float_sign().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"

#undef MAYBE_INLINE2
#define MAYBE_INLINE2 inline
#include "cl_SF_sign.cc"
#include "cl_FF_sign.cc"
#include "cl_DF_sign.cc"
#include "cl_LF_sign.cc"

const cl_F float_sign (const cl_F& x)
{
// Methode: x>=0 -> Ergebnis 1.0; x<0 -> Ergebnis -1.0
	floatcase(x
	,	return float_sign(x);
	,	return float_sign(x);
	,	return float_sign(x);
	,	return float_sign(x);
	);
}
