// cl_DF_As().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_N.h"

namespace cln {

inline cl_boolean cl_DF_p (const cl_number& x)
{
	if (x.pointer_p())
		if (x.heappointer->type == &cl_class_dfloat)
			return cl_true;
	return cl_false;
}

const cl_DF& cl_DF_As (const cl_number& x, const char * filename, int line)
{
	if (cl_DF_p(x)) {
		DeclareType(cl_DF,x);
		return x;
	} else
		cl_as_error(x,"a double-float number",filename,line);
}

}  // namespace cln
