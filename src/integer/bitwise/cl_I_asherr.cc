// cl_ash_error().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I_ash.h"


// Implementation.

#include "cln/number.h"
#include "cln/io.h"
#include "cln/integer_io.h"
#include "cln/abort.h"

namespace cln {

void cl_ash_error (const cl_I& badamount)
{
	fprint(std::cerr, "ash: too large shift amount: ");
	fprint(std::cerr, badamount);
	fprint(std::cerr, "\n");
	cl_abort();
}

}  // namespace cln
