// cl_I debugging support.

// General includes.
#include "cl_sysdep.h"

// Specification.


// Implementation.

#include "cl_integer.h"
#include "cl_io.h"
#include "cl_integer_io.h"

static void dprint (cl_heap* pointer)
{
	var const cl_I& obj = *(const cl_I*)&pointer;
	fprint(cl_debugout, "(cl_I) ");
	fprint(cl_debugout, obj);
}
AT_INITIALIZATION(dprint_I)
{
	cl_register_type_printer(cl_class_fixnum,dprint);
	cl_register_type_printer(cl_class_bignum,dprint);
}

// This dummy links in this module when <cl_integer.h> requires it.
int cl_I_debug_module;
