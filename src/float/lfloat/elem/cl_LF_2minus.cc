// binary operator -

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat.h"


// Implementation.

#include "cl_LF.h"

const cl_LF operator- (const cl_LF& x1, const cl_LF& x2)
{ GEN_LF_OP2(x1,x2,LF_LF_minus_LF,return) }
