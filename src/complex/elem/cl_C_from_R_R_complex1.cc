// complex().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_C.h"


// Implementation.

#include "cl_R.h"

namespace cln {

const cl_N complex (const cl_R& a, const cl_R& b)
{
// Methode:
// Falls b=0, nur a. sonst komplexe Zahl erzeugen.
	if (eq(b,0))
		return a;
	else
		return allocate_complex(a,b);
}

}  // namespace cln
