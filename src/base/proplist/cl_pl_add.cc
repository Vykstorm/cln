// class cl_property_list.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_proplist.h"


// Implementation.

#include "cl_abort.h"

// This tells the compiler to put the `cl_property' vtable into this file.
void cl_property::dummy () {}

void cl_property_list::add_property (cl_property* new_property)
{
	if (new_property->next)
		cl_abort();
	new_property->next = list;
	list = new_property;
}
