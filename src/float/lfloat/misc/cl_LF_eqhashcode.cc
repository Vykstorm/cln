// cl_LF equal_hashcode().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat.h"


// Implementation.

#include "cl_N.h"
#include "cl_LF_impl.h"
#include "cl_DS.h"

MAYBE_INLINE
uint32 cl_equal_hashcode (const cl_LF& x)
{
	var cl_signean sign;
	var sintL exp;
	var const uintD* MSDptr;
	LF_decode(x, { return 0; }, sign=,exp=,MSDptr=,,);
	#if (intDsize==64)
	var uint32 msd = mspref(MSDptr,0) >> 32;
	#else // (intDsize<=32)
	var uint32 msd = get_32_Dptr(MSDptr);
	#endif
	return equal_hashcode_low(msd,exp,sign);
}
