// print_real().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real_io.h"


// Implementation.

#include "cl_real.h"
#include "cl_R.h"
#include "cl_rational_io.h"
#include "cl_float_io.h"

void print_real (cl_ostream stream, const cl_print_real_flags& flags, const cl_R& z)
{
	if (rationalp(z)) {
		DeclareType(cl_RA,z);
		// rationale Zahl
		print_rational(stream,flags,z);
	} else {
		DeclareType(cl_F,z);
		// Float
		print_float(stream,flags,z);
	}
}
