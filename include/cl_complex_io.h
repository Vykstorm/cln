// I/O of complex numbers.

#ifndef _CL_COMPLEX_IO_H
#define _CL_COMPLEX_IO_H

#include "cl_number_io.h"
#include "cl_complex.h"


// Undocumented input functions

extern const cl_N read_complex (const cl_read_flags& flags, const char * string, const char * string_limit, const char * * end_of_parse);
extern const cl_N read_complex (cl_istream stream, const cl_read_flags& flags);

// Documented input functions

inline cl_istream operator>> (cl_istream stream, cl_N& result)
{
	extern cl_read_flags cl_N_read_flags;
	result = read_complex(stream,cl_N_read_flags);
	return stream;
}


// Undocumented output functions


// Documented output functions

// Gibt eine komplexe Zahl aus.
// print_complex(stream,z);
// > z: komplexe Zahl
// > stream: Stream
extern void print_complex (cl_ostream stream, const cl_print_flags& flags, const cl_N& z);
extern void print_complex (cl_ostream stream, const cl_print_number_flags& flags, const cl_N& z);

inline void fprint (cl_ostream stream, const cl_N& x)
{
	extern cl_print_flags cl_default_print_flags;
	print_complex(stream,cl_default_print_flags,x);
}

CL_DEFINE_PRINT_OPERATOR(cl_N)


#endif /* _CL_COMPLEX_IO_H */
