// cl_notreached_abort().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_macros.h"


// Implementation.

#include "cln/io.h"
#include "cln/abort.h"

namespace cln {

void cl_notreached_abort (const char* filename, int lineno)
{
	fprint(stderr, "Internal error: statement in file ");
	fprint(stderr, filename);
	fprint(stderr, ", line ");
	fprintdecimal(stderr, lineno);
	fprint(stderr, " has been reached!!\n");
	fprint(stderr, "Please send the authors of the program a description how you produced this error!\n");
	cl_abort();
}

}  // namespace cln
