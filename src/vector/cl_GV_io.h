// I/O of vectors.

#ifndef _CL_GV_IO_H
#define _CL_GV_IO_H

#include "cl_number_io.h"
#include "cl_GV.h"
#include "cl_GV_complex.h"


// Gibt einen Vektor aus.
// print_vector(stream,flags,fun,z);
// > stream: Stream
// > flags: Flags
// > fun: Ausgabefunktion für die einzelnen Elemente
// > vector: Vektor
extern void print_vector (cl_ostream stream, const cl_print_flags& flags, void (* fun) (cl_ostream, const cl_print_flags&, const cl_number&), const cl_GV_number& vector);


#endif /* _CL_GV_IO_H */
