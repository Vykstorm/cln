// minus1().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_rational.h"
#include "cl_float.h"

const cl_R minus1 (const cl_R& x)
GEN_R_OP1_2(x, minus1, return)
