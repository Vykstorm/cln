// Global variables for cl_LF.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_LF_globals)

// Specification.
#include "cl_number.h"


// Implementation.

#include "cl_LF.h"
#include "cl_LF_impl.h"

// Only needed for the default constructor of cl_LF.
const cl_LF cl_LF_0 = encode_LF0(LF_minlen); // 0.0L0

CL_PROVIDE_END(cl_LF_globals)
