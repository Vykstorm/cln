// as_cl_F().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_N.h"

inline cl_boolean cl_F_p (const cl_number& x)
{
	if (!x.pointer_p())
		switch (cl_tag((x).word)) {
		case cl_SF_tag:
		#if defined(CL_WIDE_POINTERS)
		case cl_FF_tag:
		#endif
			return cl_true;
		}
	else
		if (x.heappointer->type->flags & cl_class_flags_subclass_float)
			return cl_true;
	return cl_false;
}

const cl_F& as_cl_F (const cl_number& x, const char * filename, int line)
{
	if (cl_F_p(x)) {
		DeclareType(cl_F,x);
		return x;
	} else
		cl_as_error(x,"a floating-point number",filename,line);
}
