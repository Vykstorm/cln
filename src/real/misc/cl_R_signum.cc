// signum().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_I_signum.cc"
#include "cl_RA_signum.cc"
#undef MAYBE_INLINE2
#define MAYBE_INLINE2 inline
#include "cl_SF_signum.cc"
#include "cl_FF_signum.cc"
#include "cl_DF_signum.cc"
#include "cl_LF_signum.cc"

const cl_R signum (const cl_R& x)
GEN_R_OP1_7(x, signum, return)
