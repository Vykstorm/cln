// ceiling1().

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

const cl_I ceiling1 (const cl_F& x)
GEN_F_OP1(x, ceiling1, return)
