// read_number_eof().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/number_io.h"


// Implementation.

#include "cln/io.h"
#include "cln/abort.h"

namespace cln {

void read_number_eof (void)
{
	fprint(stderr, "read_number: end of stream encountered\n");
	cl_abort();
}

}  // namespace cln
