// unary operator -

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

const cl_F operator- (const cl_F& x)
#define minus(a) -a
GEN_F_OP1(x, minus, return)
