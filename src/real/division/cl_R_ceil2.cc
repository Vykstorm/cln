// ceiling2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_rational.h"
#include "cl_float.h"
#include "cl_R_div_t.h"

const cl_R_div_t ceiling2 (const cl_R& x)
GEN_R_OP1_2(x, ceiling2, return)
