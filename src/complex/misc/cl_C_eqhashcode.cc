// cl_N equal_hashcode().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_N.h"
#include "cl_C.h"
#include "cl_real.h"

uint32 cl_equal_hashcode (const cl_N& x)
{
	if (realp(x)) {
		DeclareType(cl_R,x);
		return cl_equal_hashcode(x);
	} else {
		DeclareType(cl_C,x);
		var const cl_R& a = realpart(x);
		var const cl_R& b = imagpart(x);
		var uint32 code1 = cl_equal_hashcode(a);
		var uint32 code2 = cl_equal_hashcode(b);
		// Wichtig beim Kombinieren, wegen "complex canonicalization":
		// Ist imagpart=0.0, so ist der Hashcode = cl_equal_hashcode(a).
		return code1 ^ ((code2 << 5) | (code2 >> 27));
	}
}
