// fprint().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/string.h"


// Implementation.

#include "cln/io.h"

namespace cln {

void fprint (std::ostream& stream, const cl_string& str)
{
	stream.write(str.asciz(),str.length());
}

}  // namespace cln
