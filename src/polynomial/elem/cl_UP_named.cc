// find_univpoly_ring().

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_UP_named)

// Specification.
#include "cln/univpoly.h"


// Implementation.

#include "cl_UP.h"

namespace cln {

// Create a new univariate polynomial ring with a named variable.

static inline cl_heap_univpoly_ring* cl_make_univpoly_ring (const cl_ring& r, const cl_symbol& varname)
{
	cl_heap_univpoly_ring* UPR = cl_make_univpoly_ring(r);
	UPR->add_property(new cl_varname_property(cl_univpoly_varname_key,varname));
	return UPR;
}

}  // namespace cln

// The table of univariate polynomial rings with named variable.
// A weak hash table (cl_ring,cl_symbol) -> cl_univpoly_ring.

#include "cl_rcpointer2_hashweak_rcpointer.h"

namespace cln {

// An entry can be collected when the value (the ring) isn't referenced any more
// except from the hash table, and when the keys (the base ring and the name)
// are't referenced any more except from the hash table and the ring. Note that
// the ring contains exactly one reference to the base ring and exactly one
// reference to the name (on the property list).

static cl_boolean maygc_htentry (const cl_htentry_from_rcpointer2_to_rcpointer& entry)
{
	if (!entry.key1.pointer_p() || (entry.key1.heappointer->refcount == 2))
		if (!entry.key2.pointer_p() || (entry.key2.heappointer->refcount == 2))
			if (!entry.val.pointer_p() || (entry.val.heappointer->refcount == 1))
				return cl_true;
	return cl_false;
}

static const cl_wht_from_rcpointer2_to_rcpointer univpoly_ring_table = cl_wht_from_rcpointer2_to_rcpointer(maygc_htentry);

static inline cl_univpoly_ring* get_univpoly_ring (const cl_ring& r, const cl_symbol& v)
{
	return (cl_univpoly_ring*) univpoly_ring_table.get(r,v);
}

static inline void store_univpoly_ring (const cl_univpoly_ring& R)
{
	univpoly_ring_table.put(R->basering(), ((cl_varname_property*)(R->get_property(cl_univpoly_varname_key)))->varname,
	                        R);
}


const cl_univpoly_ring find_univpoly_ring (const cl_ring& r, const cl_symbol& varname)
{
	var cl_univpoly_ring* ring_in_table = get_univpoly_ring(r,varname);
	if (!ring_in_table) {
		var cl_univpoly_ring R = cl_make_univpoly_ring(r,varname);
		store_univpoly_ring(R);
		ring_in_table = get_univpoly_ring(r,varname);
		if (!ring_in_table)
			cl_abort();
	}
	return *ring_in_table;
}

}  // namespace cln

CL_PROVIDE_END(cl_UP_named)
