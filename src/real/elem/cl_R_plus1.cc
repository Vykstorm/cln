// plus1().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cl_R.h"
#include "cln/rational.h"
#include "cln/float.h"

namespace cln {

const cl_R plus1 (const cl_R& x)
GEN_R_OP1_2(x, plus1, return)

}  // namespace cln
