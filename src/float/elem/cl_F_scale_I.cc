// scale_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_sfloat.h"
#include "cl_ffloat.h"
#include "cl_dfloat.h"
#include "cl_lfloat.h"
#include "cl_F.h"

const cl_F scale_float (const cl_F& x, const cl_I& delta)
{
	floatcase(x
	,	return scale_float(x,delta);
	,	return scale_float(x,delta);
	,	return scale_float(x,delta);
	,	return scale_float(x,delta);
	);
}
