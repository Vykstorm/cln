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
	fprint(std::cerr, "Internal error: statement in file ");
	fprint(std::cerr, filename);
	fprint(std::cerr, ", line ");
	fprintdecimal(std::cerr, lineno);
	fprint(std::cerr, " has been reached!!\n");
	fprint(std::cerr, "Please send the authors of the program a description how you produced this error!\n");
	cl_abort();
}

}  // namespace cln
