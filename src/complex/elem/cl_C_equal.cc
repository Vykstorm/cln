// cl_equal().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

cl_boolean cl_equal (const cl_N& x, const cl_N& y)
{
// Methode:
// Falls beide reell, klar.
// Falls x reell, y komplex: (= x (realpart y)) und (zerop (imagpart y)).
// Falls x komplex, y reell: analog
// Falls beide komplex: Realteile und Imaginärteile jeweils gleich?
	if (realp(x)) {
		DeclareType(cl_R,x);
		if (realp(y)) {
			DeclareType(cl_R,y);
			// x,y beide reell
			return cl_equal(x,y);
		} else {
			DeclareType(cl_C,y);
			// x reell, y komplex
			if (!zerop(imagpart(y)))
				return cl_false;
			return cl_equal(x,realpart(y));
		}
	} else {
		DeclareType(cl_C,x);
		if (realp(y)) {
			DeclareType(cl_R,y);
			// x komplex, y reell
			if (!zerop(imagpart(x)))
				return cl_false;
			return cl_equal(realpart(x),y);
		} else {
			DeclareType(cl_C,y);
			// x,y beide komplex
			if (!cl_equal(realpart(x),realpart(y)))
				return cl_false;
			if (!cl_equal(imagpart(x),imagpart(y)))
				return cl_false;
			return cl_true;
		}
	}
}
