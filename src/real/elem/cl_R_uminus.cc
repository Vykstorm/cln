// unary operator -

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_rational.h"
#include "cl_integer.h"
#include "cl_float.h"
#include "cl_sfloat.h"
#include "cl_ffloat.h"
#include "cl_dfloat.h"
#include "cl_lfloat.h"
#include "cl_RA.h"
#include "cl_I.h"

const cl_R operator- (const cl_R& x)
#define minus(a) -a
#if 0
GEN_R_OP1_2(x, minus, return)
#else // fully inlined, faster
GEN_R_OP1_7(x, minus, return)
#endif
