// unary operator -

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

namespace cln {

const cl_F operator- (const cl_F& x)
#define minus(a) -a
GEN_F_OP1(x, minus, return)

}  // namespace cln
