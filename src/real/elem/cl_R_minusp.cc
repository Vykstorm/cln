// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cl_R.h"
#include "cl_RA.h"
#include "cl_I.h"
#include "cl_F.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_minusp.cc"
#include "cl_FF_minusp.cc"
#include "cl_DF_minusp.cc"
#include "cl_LF_minusp.cc"

namespace cln {

bool minusp (const cl_R& x)
#if 0
GEN_R_OP1_2(x, minusp, return)
#else // fully inlined, faster
GEN_R_OP1_7(x, minusp, return)
#endif

}  // namespace cln
