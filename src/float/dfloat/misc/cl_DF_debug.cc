// cl_DF debugging support.

// General includes.
#include "cl_sysdep.h"

// Specification.


// Implementation.

#include "cl_dfloat.h"
#include "cl_io.h"
#include "cl_float_io.h"

static void dprint (cl_heap* pointer)
{
	var const cl_DF& obj = *(const cl_DF*)&pointer;
	fprint(cl_debugout, "(cl_DF) ");
	fprint(cl_debugout, obj);
}
AT_INITIALIZATION(dprint_DF)
{ cl_register_type_printer(cl_class_dfloat,dprint); }

// This dummy links in this module when <cl_dfloat.h> requires it.
int cl_DF_debug_module;
