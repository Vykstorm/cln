// binary operator -

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_rational.h"
#include "cl_float.h"

const cl_R operator- (const cl_R& x, const cl_R& y)
{
	if (eq(y,0)) { return x; }
	elif (eq(x,0)) { return -y; }
	else
#define minus(a,b) a-b
GEN_R_OP2_2(x,y, minus, return)
}
