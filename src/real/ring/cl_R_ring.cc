// Ring of real numbers.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_R_ring)

// Specification.
#include "cln/real_ring.h"


// Implementation.

#include "cln/real.h"
#include "cl_R.h"
#include "cln/io.h"
#include "cln/real_io.h"

namespace cln {

static void R_fprint (cl_heap_ring* R, std::ostream& stream, const _cl_ring_element& x)
{
	unused R;
	fprint(stream,The(cl_R)(x));
}

static cl_boolean R_equal (cl_heap_ring* R, const _cl_ring_element& x, const _cl_ring_element& y)
{
	unused R;
	return equal(The(cl_R)(x),The(cl_R)(y));
}

static const _cl_ring_element R_zero (cl_heap_ring* R)
{
	return _cl_ring_element(R, (cl_R)0);
}

static cl_boolean R_zerop (cl_heap_ring* R, const _cl_ring_element& x)
{
	unused R;
	// Here we return true only if x is the *exact* zero. Because we
	// don't want the degree of polynomials to depend on rounding errors.
	// For all ring theoretic purposes, we treat 0.0 as if it were a
	// zero divisor.
	return exact_zerop(The(cl_R)(x));
}

static const _cl_ring_element R_plus (cl_heap_ring* R, const _cl_ring_element& x, const _cl_ring_element& y)
{
	return _cl_ring_element(R, The(cl_R)(x) + The(cl_R)(y));
}

static const _cl_ring_element R_minus (cl_heap_ring* R, const _cl_ring_element& x, const _cl_ring_element& y)
{
	return _cl_ring_element(R, The(cl_R)(x) - The(cl_R)(y));
}

static const _cl_ring_element R_uminus (cl_heap_ring* R, const _cl_ring_element& x)
{
	return _cl_ring_element(R, - The(cl_R)(x));
}

static const _cl_ring_element R_one (cl_heap_ring* R)
{
	return _cl_ring_element(R, (cl_R)1);
}

static const _cl_ring_element R_canonhom (cl_heap_ring* R, const cl_I& x)
{
	return _cl_ring_element(R, (cl_R)x);
}

static const _cl_ring_element R_mul (cl_heap_ring* R, const _cl_ring_element& x, const _cl_ring_element& y)
{
	return _cl_ring_element(R, The(cl_R)(x) * The(cl_R)(y));
}

static const _cl_ring_element R_square (cl_heap_ring* R, const _cl_ring_element& x)
{
	return _cl_ring_element(R, square(The(cl_R)(x)));
}

static const _cl_ring_element R_expt_pos (cl_heap_ring* R, const _cl_ring_element& x, const cl_I& y)
{
	return _cl_ring_element(R, expt(The(cl_R)(x),y));
}

static cl_boolean cl_R_p (const cl_number& x)
{
	return (cl_boolean)
	       (!x.pointer_p()
		|| (x.pointer_type()->flags & cl_class_flags_subclass_real) != 0
	       );
}

static cl_ring_setops R_setops = {
	R_fprint,
	R_equal
};
static cl_ring_addops R_addops = {
	R_zero,
	R_zerop,
	R_plus,
	R_minus,
	R_uminus
};
static cl_ring_mulops R_mulops = {
	R_one,
	R_canonhom,
	R_mul,
	R_square,
	R_expt_pos
};

static cl_number_ring_ops<cl_R> R_ops = {
	cl_R_p,
	equal,
	exact_zerop,
	operator+,
	operator-,
	operator-,
	operator*,
	square,
	expt
};

class cl_heap_real_ring : public cl_heap_number_ring {
	SUBCLASS_cl_heap_ring()
public:
	// Constructor.
	cl_heap_real_ring ()
		: cl_heap_number_ring (&R_setops,&R_addops,&R_mulops,
		                       (cl_number_ring_ops<cl_number>*) &R_ops)
		{ type = &cl_class_real_ring; }
	// Destructor.
	~cl_heap_real_ring () {}
};

static void cl_real_ring_destructor (cl_heap* pointer)
{
	(*(cl_heap_real_ring*)pointer).~cl_heap_real_ring();
}

static void cl_real_ring_dprint (cl_heap* pointer)
{
	unused pointer;
	fprint(cl_debugout, "(cl_real_ring) cl_R_ring");
}

cl_class cl_class_real_ring = {
	cl_real_ring_destructor,
	cl_class_flags_number_ring,
	cl_real_ring_dprint
};

// Constructor.
inline cl_real_ring::cl_specialized_number_ring ()
	: cl_number_ring (new cl_heap_real_ring()) {}

const cl_real_ring cl_R_ring;

}  // namespace cln

CL_PROVIDE_END(cl_R_ring)
