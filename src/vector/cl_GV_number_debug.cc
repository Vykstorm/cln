// cl_GV_number debugging support.

// General includes.
#include "cl_sysdep.h"

// Specification.


// Implementation.

#include "cl_output.h"
#include "cl_GV_number.h"
#include "cl_io.h"
#include "cl_GV_io.h"

static void print_for_debug (cl_ostream stream, const cl_print_flags& flags, const cl_number& z)
{
	unused stream; // must be cl_debugout
	unused flags; // must be cl_default_print_flags
	z.debug_print();
}

static void dprint (cl_heap* pointer)
{
	var const cl_GV_number& obj = *(const cl_GV_number*)&pointer;
	fprint(cl_debugout, "(cl_GV_number) ");
	print_vector(cl_debugout,cl_default_print_flags,&print_for_debug,obj);
}
AT_INITIALIZATION(dprint_GV_number)
{ cl_register_type_printer(cl_class_gvector_number,dprint); }

// This dummy links in this module when <cl_GV_number.h> requires it.
int cl_GV_number_debug_module;

extern int cl_GV_I_debug_module;
static void* dummy[] = { &dummy,
	&cl_GV_I_debug_module
};
