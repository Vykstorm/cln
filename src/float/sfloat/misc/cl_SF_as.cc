// as_cl_SF().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

#include "cl_N.h"

inline cl_boolean cl_SF_p (const cl_number& x)
{
	if (!x.pointer_p())
		if (cl_tag((x).word) == cl_SF_tag)
			return cl_true;
	return cl_false;
}

const cl_SF& as_cl_SF (const cl_number& x, const char * filename, int line)
{
	if (cl_SF_p(x)) {
		DeclareType(cl_SF,x);
		return x;
	} else
		cl_as_error(x,"a short-float number",filename,line);
}
