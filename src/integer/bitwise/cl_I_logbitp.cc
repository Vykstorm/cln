// logbitp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"

namespace cln {

cl_boolean logbitp (uintL x, const cl_I& y)
{
    // Methode:
    // Falls x>=intDsize*Länge(y), teste Vorzeichen von y.
    // Sonst x=intDsize*k+i, Teste Bit i vom Worte Nr. k+1 (von oben herab).

	var const uintD* yMSDptr;
	var uintC ylen;
	var const uintD* yLSDptr;
	I_to_NDS_nocopy(y, yMSDptr=,ylen=,yLSDptr=,cl_true, { return cl_false; } ); // DS zu y
	if (x < intDsize*(uintL)ylen)
		// x ist >=0, < intDsize*ylen
		{ if (lspref(yLSDptr,floor(x,intDsize)) & bit(x%intDsize))
		    return cl_true;
		    else
		    return cl_false;
		}
	// Vorzeichen von y testen
	if (/* (ylen > 0) && */ ((sintD)mspref(yMSDptr,0) < 0))
	    return cl_true;
	    else
	    return cl_false;
}

}  // namespace cln
