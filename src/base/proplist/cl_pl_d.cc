// class cl_property_list.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_proplist.h"


// Implementation.

cl_property_list::~cl_property_list ()
{
	while (list) {
		var cl_property* l = list;
		list = l->next;
		delete l;
	}
}
