// cl_FF debugging support.

// General includes.
#include "cl_sysdep.h"

// Specification.


// Implementation.

#include "cl_ffloat.h"
#include "cl_io.h"
#include "cl_float_io.h"

static void dprint (cl_heap* pointer)
{
	var const cl_FF& obj = *(const cl_FF*)&pointer;
	fprint(cl_debugout, "(cl_FF) ");
	fprint(cl_debugout, obj);
}
AT_INITIALIZATION(dprint_FF)
{ cl_register_type_printer(cl_class_ffloat,dprint); }

// This dummy links in this module when <cl_ffloat.h> requires it.
int cl_FF_debug_module;
