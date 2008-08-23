// Version string buried into the library

// General includes.
#include "base/cl_sysdep.h"

// Specification.
#include "cln/version.h"


// Implementation.

namespace cln {

const int version_major = CL_VERSION_MAJOR;
const int version_minor = CL_VERSION_MINOR;
const int version_patchlevel = CL_VERSION_PATCHLEVEL;

}  // namespace cln
