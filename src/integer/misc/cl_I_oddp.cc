// oddp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"

namespace cln {

cl_boolean oddp (const cl_I& x)
{
	if (fixnump(x)) {
		// Fixnum: Bit 0 abprüfen
		if (x.word & bit(cl_value_shift))
			return cl_true;
		else
			return cl_false;
	} else {
		// Bignum: Bit 0 im letzten Digit abprüfen
		if (lspref(BN_LSDptr(x),0) & bit(0))
			return cl_true;
		else
			return cl_false;
	}
}

}  // namespace cln
