// Debugging stream.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_io.h"


// Implementation.

// Just assume that the debugger runs on /dev/tty, independently of
// cl_stdin, cl_stdout, cl_stderr.

#if defined(CL_IO_STDIO)

FILE* cl_debugout = fopen("/dev/tty","a");

#endif

#if defined(CL_IO_IOSTREAM)

#include <fstream.h>

ostream* cl_debugout_stream = new ofstream ("/dev/tty");

#endif
