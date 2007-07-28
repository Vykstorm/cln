// cl_LF_As().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_N.h"

namespace cln {

inline cl_boolean cl_LF_p (const cl_number& x)
{
	if (x.pointer_p())
		if (x.heappointer->type == &cl_class_lfloat)
			return cl_true;
	return cl_false;
}

const cl_LF& cl_LF_As (const cl_number& x, const char * filename, int line)
{
	if (cl_LF_p(x)) {
		DeclareType(cl_LF,x);
		return x;
	} else
		throw as_exception(x,"a long-float number",filename,line);
}

}  // namespace cln
