// asin().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

// Methode:
// Wert und Branch Cuts nach der Formel CLTL2, S. 311:
//   arcsin(z) = log(iz+sqrt(1-z^2))/i
// Sei z=x+iy, errechne u+iv = arsinh(-y+ix) wie oben, Ergebnis v-iu.
// Real- und Imagin‰rteil des Ergebnisses sind Floats, auﬂer wenn z reell oder
// rein imagin‰r ist.

inline const cl_C_R _asin (const cl_N& z)
{
	if (realp(z)) {
		DeclareType(cl_R,z);
		return asinh(0,z);
	} else {
		DeclareType(cl_C,z);
		return asinh(-imagpart(z),realpart(z));
	}
}

const cl_N asin (const cl_N& z)
{
	var cl_C_R u_v = _asin(z);
	var cl_R& u = u_v.realpart;
	var cl_R& v = u_v.imagpart;
	return complex(v,-u); // v-iu
}
