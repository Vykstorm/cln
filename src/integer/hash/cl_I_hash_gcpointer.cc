// class cl_ht_from_integer_to_gcpointer.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I_hash_gcpointer.h"


// Implementation.

#include "cl_I.h"
#include "cl_hash1.h"

static void cl_hashtable_from_integer_to_gcpointer_destructor (cl_heap* pointer)
{
#if (defined(__mips__) || defined(__mips64__)) && !defined(__GNUC__) // workaround SGI CC bug
	(*(cl_heap_hashtable_from_integer_to_gcpointer*)pointer).~cl_heap_hashtable_1();
#else
	(*(cl_heap_hashtable_from_integer_to_gcpointer*)pointer).~cl_heap_hashtable_from_integer_to_gcpointer();
#endif
}

cl_class cl_class_hashtable_from_integer_to_gcpointer = {
	cl_hashtable_from_integer_to_gcpointer_destructor,
	0
};

// These are not inline, because they tend to duplicate a lot of template code.

cl_ht_from_integer_to_gcpointer::cl_ht_from_integer_to_gcpointer ()
{
	var cl_heap_hashtable_from_integer_to_gcpointer* ht = new cl_heap_hashtable_from_integer_to_gcpointer ();
	ht->refcount = 1;
	ht->type = &cl_class_hashtable_from_integer_to_gcpointer;
	pointer = ht;
}

cl_gcpointer * cl_ht_from_integer_to_gcpointer::get (const cl_I& x) const
{
	return ((cl_heap_hashtable_from_integer_to_gcpointer*)pointer)->get(x);
}

void cl_ht_from_integer_to_gcpointer::put (const cl_I& x, const cl_gcpointer& y) const
{
	((cl_heap_hashtable_from_integer_to_gcpointer*)pointer)->put(x,y);
}

