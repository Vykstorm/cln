// cl_fgetline().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_string.h"


// Implementation.

#ifdef CL_IO_IOSTREAM

#include "cl_io.h"
#include "cl_spushstring.h"

const cl_string cl_fgetline (cl_istream stream, char delim)
{
	var cl_spushstring buffer;
	// Handling of eofp is tricky: EOF is reached when (!stream.good()) || (stream.get()==EOF).
	while (stream.good()) {
		var int c = stream.get();
		if (c==EOF)
			break;	// ios::eofbit already set
		if (c==delim)
			break;
		buffer.push(c);
	}
	return buffer.contents();
}

#endif
