// cl_compare().

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

cl_signean cl_compare (const cl_F& x, const cl_F& y)
GEN_F_OP2(x,y, cl_compare, 0, 1, return)
