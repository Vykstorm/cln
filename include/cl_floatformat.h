// Floating point format specifiers.

#ifndef _CL_FLOATFORMAT_H
#define _CL_FLOATFORMAT_H

#include "cl_types.h"

// Float format specifier type. (Float mantissa precision in bits.)
typedef enum cl_float_format_t {
	cl_float_format_sfloat = 17,
	cl_float_format_ffloat = 24,
	cl_float_format_dfloat = 53,
	cl_float_format_lfloat_min = ((53+intDsize-1)/intDsize)*intDsize // = round_up(53,intDsize)
};

#endif /* _CL_FLOATFORMAT_H */
