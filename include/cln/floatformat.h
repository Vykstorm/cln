// Floating point format specifiers.

#ifndef _CL_FLOATFORMAT_H
#define _CL_FLOATFORMAT_H

#include "cln/types.h"

namespace cln {

// Float format specifier type. (Float mantissa precision in bits.)
enum float_format_t {
	float_format_sfloat = 17,
	float_format_ffloat = 24,
	float_format_dfloat = 53,
	float_format_lfloat_min = ((53+intDsize-1)/intDsize)*intDsize // = round_up(53,intDsize)
};

}  // namespace cln

#endif /* _CL_FLOATFORMAT_H */
