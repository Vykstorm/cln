// cl_N internals

#ifndef _CL_N_H
#define _CL_N_H

#include "cln/number.h"
#include "cl_macros.h"

namespace cln {

nonreturning_function(extern, cl_error_division_by_0, (void));
nonreturning_function(extern, cl_as_error, (const cl_number& obj, const char * typestring, const char * filename, int line));

// For the equal-invariant hashcode, we take a mixture of exponent, length
// and the most significant 32 bits. To ensure that equal(x,y) implies
// equal_hashcode(x) == equal_hashcode(y) we must make sure that
// equal_hashcode(rational(x)) == equal_hashcode(x) and
// equal_hashcode(0.0) = 0 (important because of equal(complex(x,0.0),x)).
  #define equal_hashcode_low(msd,exp,sign)  \
    (((((uint32)(msd) << 7) | ((uint32)(msd) >> 25)) ^ ((sint32)(sign) << 30)) + (uintL)(exp))
  #define equal_hashcode_one  equal_hashcode_low(bit(31),1,0)

}  // namespace cln

#endif /* _CL_N_H */
