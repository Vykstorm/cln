// Built-in null ring.

#ifndef _CL_NULL_RING_H
#define _CL_NULL_RING_H

#include "cl_ring.h"

class cl_null_ring : public cl_ring { public: cl_null_ring (); };
extern const cl_null_ring cl_0_ring;		// math. {0}
//CL_REQUIRE(cl_0_ring)

#endif /* _CL_NULL_RING_H */
