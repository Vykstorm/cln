// print_integer().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer_io.h"


// Implementation.

#include "cln/io.h"
#include "cl_I.h"
#include "cl_DS.h"

namespace cln {

void print_integer (std::ostream& stream, unsigned int base, const cl_I& z)
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
#if (defined(__GNUC__) && (__GNUC__ == 3) && (__GNUC_MINOR__ < 4))
	// workaround GCC-3 compiler bug fixed in GCC-3.4.0 (cf. Debian bug#246319)
	static char dummy[40];
	snprintf(dummy,40,"%d%x%x",need,&erg,erg.LSBptr);
#endif
	I_to_digits(abs_z,(uintD)base,&erg); // Umwandlung in Ziffern
	// Ziffern ausgeben:
	{
		var uintB* ptr = erg.MSBptr;
		var uintL count = erg.len;
		do { fprintchar(stream,*ptr++); } until (--count==0);
	}
}

}  // namespace cln
