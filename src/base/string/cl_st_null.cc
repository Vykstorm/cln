// cl_null_string.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_st_null)

// Specification.
#include "cl_string.h"
extern const cl_string cl_null_string;


// Implementation.

const cl_string cl_null_string = cl_string(NULL,0);

CL_PROVIDE_END(cl_st_null)
