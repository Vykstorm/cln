// sin().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

const cl_N sin (const cl_N& x)
{
// Methode:
// x reell -> klar
// x = a+bi -> (complex (* (sin a) (cosh b)) (* (cos a) (sinh b)))
	if (realp(x)) {
		DeclareType(cl_R,x);
		return sin(x);
	} else {
		DeclareType(cl_C,x);
		// x=a+bi
		var const cl_R& a = realpart(x);
		var const cl_R& b = imagpart(x);
		var cl_cosh_sinh_t hyp_b = cl_cosh_sinh(b); // cosh(b), sinh(b) errechnen
		var cl_cos_sin_t trig_a = cl_cos_sin(a); // cos(a), sin(a) errechnen
		// Da b nicht = Fixnum 0 ist, ist auch sinh(b) nicht = Fixnum 0.
		// cos(a) /= Fixnum 0.
		return complex_C(trig_a.sin * hyp_b.cosh, // sin(a)*cosh(b)
				 trig_a.cos * hyp_b.sinh // cos(a)*sinh(b), nicht Fixnum 0
				);
	}
}
