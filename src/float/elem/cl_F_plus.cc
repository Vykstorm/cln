// binary operator +

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"
#include "cl_sfloat.h"
#include "cl_ffloat.h"
#include "cl_dfloat.h"
#include "cl_lfloat.h"
#include "cl_LF.h"

ALL_cl_LF_OPERATIONS_SAME_PRECISION()

const cl_F operator+ (const cl_F& x, const cl_F& y)
#define plus(a,b) a+b
GEN_F_OP2(x,y, plus, 1, 0, return)
