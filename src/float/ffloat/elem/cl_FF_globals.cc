// Global variables for cl_FF.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_FF_globals)

// Specification.
#include "cl_FF.h"


// Implementation.

#if !defined(CL_WIDE_POINTERS)

const cl_FF cl_FF_0 = allocate_ffloat(0); // 0.0f0

const cl_FF cl_FF_1 = encode_FF(0,1,bit(FF_mant_len)); // 1.0f0

const cl_FF cl_FF_minus1 = encode_FF(-1,1,bit(FF_mant_len)); // -1.0f0

#endif

CL_PROVIDE_END(cl_FF_globals)
