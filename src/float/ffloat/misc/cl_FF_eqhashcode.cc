// cl_FF equal_hashcode().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/ffloat.h"


// Implementation.

#include "cl_N.h"
#include "cl_FF.h"

namespace cln {

MAYBE_INLINE
uint32 equal_hashcode (const cl_FF& x)
{
	var cl_signean sign;
	var sintL exp;
	var uint32 mant;
	FF_decode(x, { return 0; }, sign=,exp=,mant=);
	var uint32 msd = mant << (32-(FF_mant_len+1));
	return equal_hashcode_low(msd,exp,sign);
}

}  // namespace cln
