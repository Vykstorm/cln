// signum().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cl_R.h"

/* use inline versions of zerop */
#include "cl_inline.h"
#include "cl_I_signum.cc"
#include "cl_RA_signum.cc"
/* use inline versions of signum */
#include "cl_inline2.h"
#include "cl_SF_signum.cc"
#include "cl_FF_signum.cc"
#include "cl_DF_signum.cc"
#include "cl_LF_signum.cc"

namespace cln {

const cl_R CL_FLATTEN signum (const cl_R& x)
GEN_R_OP1_7(x, signum_inline, return)

}  // namespace cln
