// cl_N_As().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/complex.h"


// Implementation.

#include "cl_N.h"
#include "cln/exception.h"

namespace cln {

// Cf. cl_N_p in cl_C_ring.cc.
// But here, for better inlining in g++, it is preferrable to finish every
// alternative with either "return cl_true;" or "return cl_false;".

inline cl_boolean cl_N_p (const cl_number& x)
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
		if (x.pointer_type()->flags & cl_class_flags_subclass_complex)
			return cl_true;
	return cl_false;
}

const cl_N& cl_N_As (const cl_number& x, const char * filename, int line)
{
	if (cl_N_p(x)) {
		DeclareType(cl_N,x);
		return x;
	} else
		throw as_exception(x,"a number",filename,line);
}

}  // namespace cln
