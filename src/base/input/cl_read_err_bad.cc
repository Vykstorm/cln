// read_number_bad_syntax().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/number_io.h"


// Implementation.

#include "cln/io.h"
#include "cln/abort.h"

namespace cln {

void read_number_bad_syntax (const char * string, const char * string_limit)
{
	fprint(std::cerr, "Illegal number syntax: \"");
	for (const char * ptr = string; ptr != string_limit; ptr++)
		fprintchar(std::cerr, *ptr);
	fprint(std::cerr, "\"\n");
	cl_abort();
}

}  // namespace cln
