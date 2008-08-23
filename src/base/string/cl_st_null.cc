// cl_null_string.

// General includes.
#include "base/cl_sysdep.h"

// Specification.
#include "cln/string.h"

namespace cln {

#warning "Please remove me"
extern const cl_string cl_null_string;

}  // namespace cln

// Implementation.

namespace cln {

const cl_string cl_null_string = cl_string(NULL,0);

}  // namespace cln

