// Global variables for cl_DF.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_DF_globals)

// Specification.
#include "cl_DF.h"


// Implementation.

namespace cln {

#if (cl_word_size==64)

const cl_DF cl_DF_0 = allocate_dfloat(0); // 0.0d0

const cl_DF cl_DF_1 = encode_DF(0,1,bit(DF_mant_len)); // 1.0d0

const cl_DF cl_DF_minus1 = encode_DF(-1,1,bit(DF_mant_len)); // -1.0d0

#else

const cl_DF cl_DF_0 = allocate_dfloat(0,0); // 0.0d0

const cl_DF cl_DF_1 = encode_DF(0,1,bit(DF_mant_len-32),0); // 1.0d0

const cl_DF cl_DF_minus1 = encode_DF(-1,1,bit(DF_mant_len-32),0); // -1.0d0

#endif

}  // namespace cln

CL_PROVIDE_END(cl_DF_globals)
