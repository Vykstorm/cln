// Built-in complex number ring.

#ifndef _CL_COMPLEX_RING_H
#define _CL_COMPLEX_RING_H

#include "cl_ring.h"
#include "cl_complex_class.h"

typedef cl_specialized_number_ring<cl_N> cl_complex_ring;
extern const cl_complex_ring cl_C_ring;		// math. C
extern cl_class cl_class_complex_ring;
//CL_REQUIRE(cl_C_ring)

#endif /* _CL_COMPLEX_RING_H */
