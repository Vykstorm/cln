// print_integer().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer_io.h"


// Implementation.

#include "cl_io.h"
#include "cl_I.h"
#include "cl_DS.h"

void print_integer (cl_ostream stream, unsigned int base, const cl_I& z)
{
	var cl_I abs_z;
	if (minusp(z)) {
		// z<0 -> Vorzeichen ausgeben:
		fprintchar(stream,'-');
		abs_z = -z;
	} else
		abs_z = z;
	CL_ALLOCA_STACK;
	var uintL need = cl_digits_need(abs_z,base);
	var uintB* ziffern = cl_alloc_array(uintB,need); // Platz für die Ziffern
	var cl_digits erg; erg.LSBptr = &ziffern[need];
	I_to_digits(abs_z,(uintD)base,&erg); // Umwandlung in Ziffern
	// Ziffern ausgeben:
	{
		var uintB* ptr = erg.MSBptr;
		var uintL count = erg.len;
		do { fprintchar(stream,*ptr++); } until (--count==0);
	}
}
