// rational().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"

const cl_RA rational (const cl_R& x)
GEN_R_OP1_2(x, rational, return)
