// cl_decimal_string().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer_io.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"
#include "cl_sstring.h"

namespace cln {

char * cl_decimal_string (const cl_I& x)
{
	CL_ALLOCA_STACK;
	var uintL need = cl_digits_need(x,10);
	var uintB* ziffern = cl_alloc_array(uintB,need); // Platz für die Ziffern
	var cl_digits erg; erg.LSBptr = &ziffern[need];
	I_to_digits(x,10,&erg); // Umwandlung in Ziffern
	var char* result = cl_sstring((char*)erg.MSBptr,erg.len); // Ziffern in String schreiben
	return result;
}

}  // namespace cln
