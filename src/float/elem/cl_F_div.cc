// binary operator /

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"
#include "cln/sfloat.h"
#include "cln/ffloat.h"
#include "cln/dfloat.h"
#include "cln/lfloat.h"
#include "cl_LF.h"

namespace cln {

ALL_cl_LF_OPERATIONS_SAME_PRECISION()

const cl_F operator/ (const cl_F& x, const cl_F& y)
#define div(a,b) a/b
GEN_F_OP2(x,y, div, 1, 1, return)

}  // namespace cln
