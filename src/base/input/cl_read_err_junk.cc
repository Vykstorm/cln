// read_number_junk().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/number_io.h"


// Implementation.

#include "cln/io.h"
#include "cln/abort.h"

namespace cln {

void read_number_junk (const char * string_rest, const char * string, const char * string_limit)
{
	fprint(std::cerr, "Junk after number: ");
	{ for (const char * ptr = string; ptr != string_rest; ptr++)
		fprintchar(std::cerr, *ptr);
	}
	fprint(std::cerr, "\"");
	{ for (const char * ptr = string_rest; ptr != string_limit; ptr++)
		fprintchar(std::cerr, *ptr);
	}
	fprint(std::cerr, "\"\n");
	cl_abort();
}

}  // namespace cln
