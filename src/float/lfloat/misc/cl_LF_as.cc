// as_cl_LF().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat.h"


// Implementation.

#include "cl_N.h"

inline cl_boolean cl_LF_p (const cl_number& x)
{
	if (x.pointer_p())
		if (x.heappointer->type == &cl_class_lfloat)
			return cl_true;
	return cl_false;
}

const cl_LF& as_cl_LF (const cl_number& x, const char * filename, int line)
{
	if (cl_LF_p(x)) {
		DeclareType(cl_LF,x);
		return x;
	} else
		cl_as_error(x,"a long-float number",filename,line);
}
