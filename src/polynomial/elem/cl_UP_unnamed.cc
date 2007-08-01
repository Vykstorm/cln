// find_univpoly_ring().

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_UP_unnamed)

// Specification.
#include "cln/univpoly.h"


// Implementation.

#include "cl_UP.h"

// The table of univariate polynomial rings without named variable.
// A weak hash table cl_ring -> cl_univpoly_ring.
// (It could also be a weak hashuniq table cl_ring -> cl_univpoly_ring.)

#include "cl_rcpointer_hashweak_rcpointer.h"

namespace cln {

// An entry can be collected when the value (the ring) isn't referenced any more
// except from the hash table, and when the key (the base ring) isn't referenced
// any more except from the hash table and the ring. Note that the ring contains
// exactly one reference to the base ring.

static bool maygc_htentry (const cl_htentry_from_rcpointer_to_rcpointer& entry)
{
	if (!entry.key.pointer_p() || (entry.key.heappointer->refcount == 2))
		if (!entry.val.pointer_p() || (entry.val.heappointer->refcount == 1))
			return true;
	return false;
}

static const cl_wht_from_rcpointer_to_rcpointer univpoly_ring_table = cl_wht_from_rcpointer_to_rcpointer(maygc_htentry);

static inline cl_univpoly_ring* get_univpoly_ring (const cl_ring& r)
{
	return (cl_univpoly_ring*) univpoly_ring_table.get(r);
}

static inline void store_univpoly_ring (const cl_univpoly_ring& R)
{
	univpoly_ring_table.put(R->basering(),R);
}


const cl_univpoly_ring find_univpoly_ring (const cl_ring& r)
{
	var cl_univpoly_ring* ring_in_table = get_univpoly_ring(r);
	if (!ring_in_table) {
		var cl_univpoly_ring R = cl_make_univpoly_ring(r);
		store_univpoly_ring(R);
		ring_in_table = get_univpoly_ring(r);
		if (!ring_in_table)
			throw runtime_exception();
	}
	return *ring_in_table;
}

}  // namespace cln

CL_PROVIDE_END(cl_UP_unnamed)
