// class cl_property_list.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_proplist.h"


// Implementation.

cl_property* cl_property_list::get_property (const cl_symbol& key)
{
	var cl_property* l;
	for (l = list; l; l = l->next)
		if (equal(l->key,key))
			break;
	return l;
}
