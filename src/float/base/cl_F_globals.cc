// Global variables in CLN

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

namespace cln {

cl_boolean cl_inhibit_floating_point_underflow = cl_false;

float_format_t default_float_format      = float_format_ffloat;

}  // namespace cln
