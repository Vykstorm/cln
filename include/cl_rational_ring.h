// Built-in rational number ring.

#ifndef _CL_RATIONAL_RING_H
#define _CL_RATIONAL_RING_H

#include "cl_ring.h"
#include "cl_rational_class.h"

typedef cl_specialized_number_ring<cl_RA> cl_rational_ring;
extern const cl_rational_ring cl_RA_ring;	// math. Q
extern cl_class cl_class_rational_ring;
//CL_REQUIRE(cl_RA_ring)

#endif /* _CL_RATIONAL_RING_H */
