// class cl_ht_from_integer_to_pointer.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I_hash_pointer.h"


// Implementation.

#include "cl_I.h"
#include "cl_hash1.h"

static void cl_hashtable_from_integer_to_pointer_destructor (cl_heap* pointer)
{
#if (defined(__mips__) || defined(__mips64__)) && !defined(__GNUC__) // workaround SGI CC bug
	(*(cl_heap_hashtable_from_integer_to_pointer*)pointer).~cl_heap_hashtable_1();
#else
	(*(cl_heap_hashtable_from_integer_to_pointer*)pointer).~cl_heap_hashtable_from_integer_to_pointer();
#endif
}

cl_class cl_class_hashtable_from_integer_to_pointer = {
	cl_hashtable_from_integer_to_pointer_destructor,
	0
};

// These are not inline, because they tend to duplicate a lot of template code.

cl_ht_from_integer_to_pointer::cl_ht_from_integer_to_pointer ()
{
	var cl_heap_hashtable_from_integer_to_pointer* ht = new cl_heap_hashtable_from_integer_to_pointer ();
	ht->refcount = 1;
	ht->type = &cl_class_hashtable_from_integer_to_pointer;
	pointer = ht;
}

void* * cl_ht_from_integer_to_pointer::get (const cl_I& x) const
{
	return ((cl_heap_hashtable_from_integer_to_pointer*)pointer)->get(x);
}

void cl_ht_from_integer_to_pointer::put (const cl_I& x, void* y) const
{
	((cl_heap_hashtable_from_integer_to_pointer*)pointer)->put(x,y);
}

