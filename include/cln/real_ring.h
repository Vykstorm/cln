// Built-in real number ring.

#ifndef _CL_REAL_RING_H
#define _CL_REAL_RING_H

#include "cln/ring.h"
#include "cln/real_class.h"

namespace cln {

typedef cl_specialized_number_ring<cl_R> cl_real_ring;
extern const cl_real_ring cl_R_ring;		// math. R
extern cl_class cl_class_real_ring;
//CL_REQUIRE(cl_R_ring)

}  // namespace cln

#endif /* _CL_REAL_RING_H */
