// integer_decode_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"

#include "cl_inline.h"
#include "cl_SF_idecode.cc"
#include "cl_FF_idecode.cc"
#include "cl_DF_idecode.cc"
#include "cl_LF_idecode.cc"

namespace cln {

const cl_idecoded_float CL_FLATTEN integer_decode_float (const cl_F& x)
{
	floatcase(x
	,	return integer_decode_float_inline(x);
	,	return integer_decode_float_inline(x);
	,	return integer_decode_float_inline(x);
	,	return integer_decode_float_inline(x);
	);
}

}  // namespace cln
