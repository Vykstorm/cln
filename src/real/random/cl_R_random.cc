// random_R().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_RA.h"
#include "cl_io.h"
#include "cl_real_io.h"
#include "cl_abort.h"

const cl_R random_R (cl_random_state& r, const cl_R& n)
{
	// n muß eine reelle Zahl sein, >0 und Float oder Integer
	if (plusp(n)) {
		if (floatp(n)) {
			DeclareType(cl_F,n);
			return random_F(r,n);
		} else {
			DeclareType(cl_RA,n);
			if (integerp(n)) {
				DeclareType(cl_I,n);
				return random_I(r,n);
			}
		}
	}
	fprint(cl_stderr, "random: argument should be positive and an integer or float: ");
	fprint(cl_stderr, n);
	fprint(cl_stderr, "\n");
	cl_abort();
}
