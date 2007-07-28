// cl_RA_As().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/rational.h"


// Implementation.

#include "cl_N.h"

namespace cln {

// Cf. cl_RA_p in cl_RA_ring.cc.
// But here, for better inlining in g++, it is preferrable to finish every
// alternative with either "return cl_true;" or "return cl_false;".

inline cl_boolean cl_RA_p (const cl_number& x)
{
	if (!x.pointer_p())
		switch (x.nonpointer_tag()) {
		case cl_FN_tag:
			return cl_true;
		}
	else
		if (x.pointer_type()->flags & cl_class_flags_subclass_rational)
			return cl_true;
	return cl_false;
}

const cl_RA& cl_RA_As (const cl_number& x, const char * filename, int line)
{
	if (cl_RA_p(x)) {
		DeclareType(cl_RA,x);
		return x;
	} else
		throw as_exception(x,"a rational number",filename,line);
}

}  // namespace cln
