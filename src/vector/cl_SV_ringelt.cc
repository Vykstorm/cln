// cl_make_heap_SV_ringelt().

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_SV_ringelt)

// Specification.
#include "cln/SV_ringelt.h"


// Implementation.

namespace cln {

static void cl_svector_ringelt_destructor (cl_heap* pointer)
{
#if (defined(__mips__) || defined(__mips64__)) && !defined(__GNUC__) // workaround SGI CC bug
	(*(cl_heap_SV_ringelt*)pointer).~cl_heap_SV();
#else
	(*(cl_heap_SV_ringelt*)pointer).~cl_heap_SV_ringelt();
#endif
}

cl_class cl_class_svector_ringelt = {
	cl_svector_ringelt_destructor,
	0
};

cl_heap_SV_ringelt* cl_make_heap_SV_ringelt_uninit (uintC len)
{
	var cl_heap_SV_ringelt* hv = (cl_heap_SV_ringelt*) malloc_hook(sizeof(cl_heap_SV_ringelt)+sizeof(_cl_ring_element)*len);
	hv->refcount = 1;
	hv->type = &cl_class_svector_ringelt;
	new (&hv->v) cl_SV_inner<_cl_ring_element> (len);
	// Have to fill hv->v[i] (0 <= i < len) yourself.
	return hv;
}

cl_heap_SV_ringelt* cl_make_heap_SV_ringelt (uintC len)
{
	var cl_heap_SV_ringelt* hv = (cl_heap_SV_ringelt*) malloc_hook(sizeof(cl_heap_SV_ringelt)+sizeof(_cl_ring_element)*len);
	hv->refcount = 1;
	hv->type = &cl_class_svector_ringelt;
	new (&hv->v) cl_SV_inner<_cl_ring_element> (len);
	for (var uintC i = 0; i < len; i++)
		init1(_cl_ring_element, hv->v[i]) ();
	return hv;
}

// An empty vector.
const cl_SV_ringelt cl_null_SV_ringelt = cl_SV_ringelt((uintC)0);

}  // namespace cln

CL_PROVIDE_END(cl_SV_ringelt)
