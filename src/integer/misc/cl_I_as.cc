// cl_I_As().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cl_N.h"

namespace cln {

// Cf. cl_I_p in cl_I_ring.cc.
// But here, for better inlining in g++, it is preferrable to finish every
// alternative with either "return cl_true;" or "return cl_false;".

inline cl_boolean cl_I_p (const cl_number& x)
{
	if (!x.pointer_p())
		switch (x.nonpointer_tag()) {
		case cl_FN_tag:
			return cl_true;
		}
	else
		if (x.pointer_type() == &cl_class_bignum)
			return cl_true;
	return cl_false;
}

const cl_I& cl_I_As (const cl_number& x, const char * filename, int line)
{
	if (cl_I_p(x)) {
		DeclareType(cl_I,x);
		return x;
	} else
		cl_as_error(x,"an integer",filename,line);
}

}  // namespace cln
