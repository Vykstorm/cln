// cl_error_exquo().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I.h"


// Implementation.

#include "cln/io.h"
#include "cln/integer_io.h"
#include "cln/abort.h"

namespace cln {

void cl_error_exquo (const cl_I& x, const cl_I& y)
{
	fprint(std::cerr, "Quotient ");
	fprint(std::cerr, x);
	fprint(std::cerr, " / ");
	fprint(std::cerr, y);
	fprint(std::cerr, " is not an integer.\n");
	cl_abort();
}

}  // namespace cln
