// as_cl_FF().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_ffloat.h"


// Implementation.

#include "cl_N.h"

inline cl_boolean cl_FF_p (const cl_number& x)
{
#if defined(CL_WIDE_POINTERS)
	if (!x.pointer_p())
		if (cl_tag((x).word) == cl_FF_tag)
			return cl_true;
#else
	if (x.pointer_p())
		if (x.heappointer->type == &cl_class_ffloat)
			return cl_true;
#endif
	return cl_false;
}

const cl_FF& as_cl_FF (const cl_number& x, const char * filename, int line)
{
	if (cl_FF_p(x)) {
		DeclareType(cl_FF,x);
		return x;
	} else
		cl_as_error(x,"a single-float number",filename,line);
}
