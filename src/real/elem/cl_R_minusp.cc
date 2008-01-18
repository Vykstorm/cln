// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cl_R.h"
#define minusp minusp_inline
#include "cl_RA.h"
#include "cl_I.h"
#undef minusp
#include "cl_F.h"

#include "cl_inline.h"
#include "cl_SF_minusp.cc"
#include "cl_FF_minusp.cc"
#include "cl_DF_minusp.cc"
#include "cl_LF_minusp.cc"

namespace cln {

bool CL_FLATTEN minusp (const cl_R& x)
#if 0
GEN_R_OP1_2(x, minusp, return)
#else // fully inlined, faster
GEN_R_OP1_7(x, minusp_inline, return)
#endif

}  // namespace cln
