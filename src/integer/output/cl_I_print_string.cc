// print_integer_to_string().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer_io.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"
#include "cl_sstring.h"

char * print_integer_to_string (unsigned int base, const cl_I& z)
{
	var cl_boolean minus_p = cl_false;
	var cl_I abs_z;
	if (minusp(z)) {
		// z<0 -> später Vorzeichen ausgeben:
		minus_p = cl_true;
		abs_z = -z;
	} else
		abs_z = z;
	CL_ALLOCA_STACK;
	var uintL need = 1+cl_digits_need(abs_z,base);
	var uintB* ziffern = cl_alloc_array(uintB,need); // Platz für die Ziffern
	var cl_digits erg; erg.LSBptr = &ziffern[need];
	I_to_digits(abs_z,(uintD)base,&erg); // Umwandlung in Ziffern
	// Vorzeichen ankleben:
	var char* ergptr = (char*)erg.MSBptr;
	var uintL erglen = erg.len;
	if (minus_p) {
		*--ergptr = '-';
		erglen++;
	}
	var char* result = cl_sstring(ergptr,erglen); // Ziffern in String schreiben
	return result;
}
