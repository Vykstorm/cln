// round2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cl_R.h"
#include "cln/rational.h"
#include "cln/float.h"
#include "cl_R_div_t.h"

namespace cln {

const cl_R_div_t round2 (const cl_R& x)
GEN_R_OP1_2(x, round2, return)

}  // namespace cln
