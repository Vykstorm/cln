// cl_R equal_hashcode().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cl_N.h"
#include "cl_R.h"
#include "cl_RA.h"
#include "cl_I.h"
#include "cl_F.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_I_eqhashcode.cc"
#include "cl_SF_eqhashcode.cc"
#include "cl_FF_eqhashcode.cc"
#include "cl_DF_eqhashcode.cc"
#include "cl_LF_eqhashcode.cc"

namespace cln {

uint32 equal_hashcode (const cl_R& x)
GEN_R_OP1_7(x, equal_hashcode, return)

}  // namespace cln
