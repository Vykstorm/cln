// NUDS_to_I().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I.h"


// Implementation.

#include "cln/number.h"
#include "cl_DS.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_I_from_NDS.cc"

namespace cln {

MAYBE_INLINE2
const cl_I NUDS_to_I (uintD* MSDptr, uintC len)
{
	if ((!(len==0)) && ((sintD)mspref(MSDptr,0) < 0))
		// Falls die Länge >0 und das Most significant Bit = 1 sind,
		// die Digit Sequence um ein Nulldigit erweitern:
		{ lsprefnext(MSDptr) = 0; len++; }
	return NDS_to_I(MSDptr,len);
}

}  // namespace cln
