// atan().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

const cl_R atan (const cl_R& x)
{
// Methode:
// arctan(x) = arctan(X=1,Y=x).
	return atan(1,x);
}
