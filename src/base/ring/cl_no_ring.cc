// Dummy ring.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_no_ring)

// Specification.
#include "cln/ring.h"


// Implementation.

#include "cln/io.h"
#include "cln/abort.h"

namespace cln {

nonreturning_function(static, uninitialized_ring, (void));
static void uninitialized_ring ()
{
	fprint(stderr, "Uninitialized ring operation called\n");
	cl_abort();
}

nonreturning_function(static, uninitialized_error, (const _cl_ring_element&));
static void uninitialized_error (const _cl_ring_element& obj)
{
	fprint(stderr, "Uninitialized ring element @0x");
	fprinthexadecimal(stderr, (unsigned long)(void*)&obj);
	fprint(stderr, ": 0x");
        fprinthexadecimal(stderr, (unsigned long)obj.rep.word);
	fprint(stderr, "\n");
	cl_abort();
}

#if (defined(__sparc__) && !defined(__GNUC__))
  // avoid Sun C++ 4.1 compiler bug
  #define RETDUMMY  return *(_cl_ring_element*)R
#else
  #define RETDUMMY  return *(_cl_ring_element*)0
#endif

static const _cl_ring_element dummy_op0 (cl_heap_ring* R)
{
	unused R;
	uninitialized_ring(); RETDUMMY;
}

static const _cl_ring_element dummy_op1 (cl_heap_ring* R, const _cl_ring_element& x)
{
	unused R;
	uninitialized_error(x); RETDUMMY;
}

static const _cl_ring_element dummy_op2 (cl_heap_ring* R, const _cl_ring_element& x, const _cl_ring_element& y)
{
	unused R;
	uninitialized_error(x); uninitialized_error(y); RETDUMMY;
}

static void dummy_fprint (cl_heap_ring* R, cl_ostream stream, const _cl_ring_element& x)
{
	unused R;
	unused stream;
	uninitialized_error(x);
}
static cl_boolean dummy_equal (cl_heap_ring* R, const _cl_ring_element& x, const _cl_ring_element& y)
{
	unused R;
	uninitialized_error(x); uninitialized_error(y); return cl_false;
}

#define dummy_zero dummy_op0
static cl_boolean dummy_zerop (cl_heap_ring* R, const _cl_ring_element& x)
{
	unused R;
	uninitialized_error(x); return cl_false;
}
#define dummy_plus dummy_op2
#define dummy_minus dummy_op2
#define dummy_uminus dummy_op1

#define dummy_one dummy_op0
static const _cl_ring_element dummy_canonhom (cl_heap_ring* R, const cl_I& x)
{
	unused R;
	(void)&x; // unused x;
	uninitialized_ring(); RETDUMMY;
}
#define dummy_mul dummy_op2
#define dummy_square dummy_op1
static const _cl_ring_element dummy_expt_pos (cl_heap_ring* R, const _cl_ring_element& x, const cl_I& y)
{
	unused R;
	(void)&y; // unused y;
	uninitialized_error(x); RETDUMMY;
}

static cl_ring_setops dummy_setops = {
	dummy_fprint,
	dummy_equal
};
static cl_ring_addops dummy_addops = {
	dummy_zero,
	dummy_zerop,
	dummy_plus,
	dummy_minus,
	dummy_uminus
};
static cl_ring_mulops dummy_mulops = {
	dummy_one,
	dummy_canonhom,
	dummy_mul,
	dummy_square,
	dummy_expt_pos
};

class cl_heap_no_ring : public cl_heap_ring {
	SUBCLASS_cl_heap_ring()
public:
	// Constructor.
	cl_heap_no_ring ()
		: cl_heap_ring (&dummy_setops,&dummy_addops,&dummy_mulops)
		{ type = &cl_class_no_ring; }
	// Destructor.
	~cl_heap_no_ring () {}
};

static void cl_no_ring_destructor (cl_heap* pointer)
{
	(*(cl_heap_no_ring*)pointer).~cl_heap_no_ring();
}

static void cl_no_ring_dprint (cl_heap* pointer)
{
	unused pointer;
	fprint(cl_debugout, "(cl_ring) cl_no_ring");
}

cl_class cl_class_no_ring = {
	cl_no_ring_destructor,
	0,
	cl_no_ring_dprint
};

const cl_ring cl_no_ring = cl_ring (new cl_heap_no_ring());

}  // namespace cln

CL_PROVIDE_END(cl_no_ring)
