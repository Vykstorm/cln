// as_cl_R().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_N.h"

// Cf. cl_R_p in cl_R_ring.cc.
// But here, for better inlining in g++, it is preferrable to finish every
// alternative with either "return cl_true;" or "return cl_false;".

inline cl_boolean cl_R_p (const cl_number& x)
{
	if (!x.pointer_p())
		switch (x.nonpointer_tag()) {
		case cl_FN_tag:
		case cl_SF_tag:
		#if defined(CL_WIDE_POINTERS)
		case cl_FF_tag:
		#endif
			return cl_true;
		}
	else
		if (x.pointer_type()->flags & cl_class_flags_subclass_real)
			return cl_true;
	return cl_false;
}

const cl_R& as_cl_R (const cl_number& x, const char * filename, int line)
{
	if (cl_R_p(x)) {
		DeclareType(cl_R,x);
		return x;
	} else
		cl_as_error(x,"a real number",filename,line);
}
