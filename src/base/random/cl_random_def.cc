// default_random_state.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_random_def)

// Specification.
#include "cln/random.h"


// Implementation.

namespace cln {
	
random_state default_random_state;

}  // namespace cln

CL_PROVIDE_END(cl_random_def)
