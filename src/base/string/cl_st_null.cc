// cl_null_string.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_st_null)

// Specification.
#include "cln/string.h"

namespace cln {

extern const cl_string cl_null_string;

}  // namespace cln

// Implementation.

namespace cln {

const cl_string cl_null_string = cl_string(NULL,0);

}  // namespace cln

CL_PROVIDE_END(cl_st_null)
