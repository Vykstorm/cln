// sqrt().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cl_R.h"
#include "cln/float.h"
#include "cln/rational.h"

namespace cln {

#include "cl_inline.h"
#include "cl_RA_sqrt.cc"

const cl_R sqrt (const cl_R& x)
GEN_R_OP1_2(x, sqrt, return)

}  // namespace cln
