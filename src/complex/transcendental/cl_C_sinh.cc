// sinh().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

const cl_N sinh (const cl_N& x)
{
// Methode:
// x reell -> klar
// x = a+bi -> (complex (* (sinh a) (cos b)) (* (cosh a) (sin b)))
	if (realp(x)) {
		DeclareType(cl_R,x);
		return sinh(x);
	} else {
		DeclareType(cl_C,x);
		// x=a+bi
		var const cl_R& a = realpart(x);
		var const cl_R& b = imagpart(x);
		var cl_cosh_sinh_t hyp_a = cl_cosh_sinh(a); // cosh(a), sinh(a) errechnen
		var cl_cos_sin_t trig_b = cl_cos_sin(b); // cos(b), sin(b) errechnen
		// Da b nicht = Fixnum 0 ist, ist auch sin(b) nicht = Fixnum 0.
		// cosh(a) /= Fixnum 0.
		return complex_C(hyp_a.sinh * trig_b.cos, // sinh(a)*cos(b)
				 hyp_a.cosh * trig_b.sin // cosh(a)*sin(b), nicht Fixnum 0
				);
	}
}
