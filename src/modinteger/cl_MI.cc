// Modular integer operations.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_MI)

// Specification.
#include "cln/modinteger.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"
#include "cl_2DS.h"
#include "cln/io.h"
#include "cln/integer_io.h"
#include "cl_N.h"
#include "cl_MI.h"
#include "cln/abort.h"
#include "cl_alloca.h"

// MacOS X does "#define _R 0x00040000L"
// Grr...
#undef _R

namespace cln {

static void cl_modint_ring_destructor (cl_heap* pointer)
{
	(*(cl_heap_modint_ring*)pointer).~cl_heap_modint_ring();
}

cl_class cl_class_modint_ring = {
	cl_modint_ring_destructor,
	cl_class_flags_modint_ring
};

cl_heap_modint_ring::cl_heap_modint_ring (cl_I m, cl_modint_setops* setopv, cl_modint_addops* addopv, cl_modint_mulops* mulopv)
	: setops (setopv), addops (addopv), mulops (mulopv), modulus (m)
{
	refcount = 0; // will be incremented by the `cl_modint_ring' constructor
	type = &cl_class_modint_ring;
	if (minusp(m)) cl_abort();
	if (!cln::zerop(m)) {
		var uintC b = integer_length(m-1);
		// m <= 2^b, hence one needs b bits for a representative mod m.
		if (b <= 1) {
			log2_bits = 0; bits = 1;
		} else if (b <= cl_word_size) {
			var uintL bb;
			integerlengthC(b-1,bb=); // b <= 2^bb with bb minimal
			log2_bits = bb; bits = 1<<bb;
		} else {
			log2_bits = -1; bits = -1;
		}
	} else {
		log2_bits = -1; bits = -1;
	}
}


static cl_boolean modint_equal (cl_heap_modint_ring* R, const _cl_MI& x, const _cl_MI& y)
{
	unused R;
	return equal(x.rep,y.rep);
}

}  // namespace cln
#include "cl_MI_int.h"
#include "cl_MI_std.h"
#include "cl_MI_fix16.h"
#if (cl_value_len <= 32)
#include "cl_MI_fix29.h"
#include "cl_MI_int32.h"
#else
#include "cl_MI_fix32.h"
#endif
#include "cl_MI_pow2.h"
#include "cl_MI_pow2m1.h"
#include "cl_MI_pow2p1.h"
#include "cl_MI_montgom.h"
namespace cln {


static inline cl_heap_modint_ring* make_modint_ring (const cl_I& m) // m >= 0
{
	if (m == 0)
		return new cl_heap_modint_ring_int();
	// Now m > 0.
	{
		var uintC log2_m = power2p(m);
		if (log2_m)
			return new cl_heap_modint_ring_pow2(m,log2_m-1);
	}
	// Now m > 1.
	{
		var uintC log2_m = integer_length(m); // = integerlength(m-1)
		if (log2_m < 16) // m < 0x10000
			return new cl_heap_modint_ring_fix16(m);
		#if (cl_value_len <= 32)
		if (log2_m < cl_value_len)
			return new cl_heap_modint_ring_fix29(m);
		if (log2_m < 32) // m < 0x100000000
			return new cl_heap_modint_ring_int32(m);
		#else
		if (log2_m < 32) // m < 0x100000000
			return new cl_heap_modint_ring_fix32(m);
		#endif
	}
	{
		var uintC m1 = power2p(m+1);
		if (m1)
			return new cl_heap_modint_ring_pow2m1(m,m1-1);
	}
	{
		var uintC m1 = power2p(m-1);
		if (m1)
			return new cl_heap_modint_ring_pow2p1(m,m1-1);
	}
	{
		var cl_heap_modint_ring* R = try_make_modint_ring_montgom(m);
		if (R)
			return R;
	}
	return new cl_heap_modint_ring_std(m);
}


// The table of modular integer rings.
// A weak hash table cl_I -> cl_modint_ring.
// (It could also be a weak hashuniq table cl_I -> cl_modint_ring.)

}  // namespace cln
#include "cl_I_hashweak_rcpointer.h"
namespace cln {

// An entry can be collected when the value (the ring) isn't referenced any more
// except from the hash table, and when the key (the modulus) isn't referenced
// any more except from the hash table and the ring. Note that the ring contains
// exactly one reference to the modulus.

static cl_boolean maygc_htentry (const cl_htentry_from_integer_to_rcpointer& entry)
{
	if (!entry.key.pointer_p() || (entry.key.heappointer->refcount == 2))
		if (!entry.val.pointer_p() || (entry.val.heappointer->refcount == 1))
			return cl_true;
	return cl_false;
}

static const cl_wht_from_integer_to_rcpointer modint_ring_table = cl_wht_from_integer_to_rcpointer(maygc_htentry);

static inline cl_modint_ring* get_modint_ring (const cl_I& m)
{
	return (cl_modint_ring*) modint_ring_table.get(m);
}

static inline void store_modint_ring (const cl_modint_ring& R)
{
	modint_ring_table.put(R->modulus,R);
}


const cl_modint_ring find_modint_ring (const cl_I& m)
{
 {	Mutable(cl_I,m);
	m = abs(m);
	var cl_modint_ring* ring_in_table = get_modint_ring(m);
	if (!ring_in_table) {
		var cl_modint_ring R = make_modint_ring(m);
		store_modint_ring(R);
		ring_in_table = get_modint_ring(m);
		if (!ring_in_table)
			cl_abort();
	}
	return *ring_in_table;
}}


const cl_modint_ring cl_modint0_ring = find_modint_ring(0);

}  // namespace cln

CL_PROVIDE_END(cl_MI)
