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
	fprint(stderr, "Type assertion failed: in file ");
	fprint(stderr, filename);
	fprint(stderr, ", line ");
	fprintdecimal(stderr, line);
	fprint(stderr, ", not ");
	fprint(stderr, typestring);
	fprint(stderr, ": ");
#if 0 // This brings in a dependency from the complex and float printer and all the float stuff.
	fprint(stderr, obj);
#else
	fprint(stderr, "@0x");
	fprinthexadecimal(stderr, (unsigned long)(void*)&obj);
	fprint(stderr, ": 0x");
	fprinthexadecimal(stderr, (unsigned long)obj.word);
#endif
	fprint(stderr, "\n");
	cl_abort();
}

}  // namespace cln
