// sqrt().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_float.h"
#include "cl_rational.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_RA_sqrt.cc"

const cl_R sqrt (const cl_R& x)
GEN_R_OP1_2(x, sqrt, return)
