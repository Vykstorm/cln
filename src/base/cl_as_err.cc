// cl_as_error().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_N.h"


// Implementation.

#include "cln/io.h"
#include "cln/abort.h"

namespace cln {

void cl_as_error (const cl_number& obj, const char * typestring, const char * filename, int line)
{
	fprint(std::cerr, "Type assertion failed: in file ");
	fprint(std::cerr, filename);
	fprint(std::cerr, ", line ");
	fprintdecimal(std::cerr, line);
	fprint(std::cerr, ", not ");
	fprint(std::cerr, typestring);
	fprint(std::cerr, ": ");
#if 0 // This brings in a dependency from the complex and float printer and all the float stuff.
	fprint(std::cerr, obj);
#else
	fprint(std::cerr, "@0x");
	fprinthexadecimal(std::cerr, (unsigned long)(void*)&obj);
	fprint(std::cerr, ": 0x");
	fprinthexadecimal(std::cerr, (unsigned long)obj.word);
#endif
	fprint(std::cerr, "\n");
	cl_abort();
}

}  // namespace cln
