// I/O of dfloats.

#ifndef _CL_DFLOAT_IO_H
#define _CL_DFLOAT_IO_H

#include "cl_number_io.h"
#include "cl_dfloat.h"

inline cl_istream operator>> (cl_istream stream, cl_DF& result)
{
	extern cl_read_flags cl_DF_read_flags;
	extern const cl_F read_float (cl_istream, const cl_read_flags&);
	result = As(cl_DF)(read_float(stream,cl_DF_read_flags));
	return stream;
}

// The following does strictly the same as the general `fprint' for floats.
// It is here only so that people don't need to include <cl_float_io.h>.
inline void fprint (cl_ostream stream, const cl_DF& x)
{
	extern void print_float (cl_ostream stream, const cl_print_flags& flags, const cl_F& z);
	extern cl_print_flags cl_default_print_flags;
	print_float(stream,cl_default_print_flags,x);
}
CL_DEFINE_PRINT_OPERATOR(cl_DF)

#endif /* _CL_DFLOAT_IO_H */
