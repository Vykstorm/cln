// tan().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

const cl_N tan (const cl_N& x)
{
// Methode:
// x reell -> (/ (sin x) (cos x))
// x = a+bi -> (/ (complex (* (sin a) (cosh b)) (* (cos a) (sinh b)))
//                (complex (* (cos a) (cosh b)) (- (* (sin a) (sinh b)))) )
	if (realp(x)) {
		DeclareType(cl_R,x);
		var cl_cos_sin_t trig = cl_cos_sin(x);
		return trig.sin / trig.cos;
	} else {
		DeclareType(cl_C,x);
		// x=a+bi
		var const cl_R& a = realpart(x);
		var const cl_R& b = imagpart(x);
		var cl_cosh_sinh_t hyp_b = cl_cosh_sinh(b); // cosh(b), sinh(b) errechnen
		var cl_cos_sin_t trig_a = cl_cos_sin(a); // cos(a), sin(a) errechnen
		return
			complex_C(trig_a.sin * hyp_b.cosh, // sin(a)*cosh(b)
				  trig_a.cos * hyp_b.sinh // cos(a)*sinh(b), nicht Fixnum 0
				 )
		      /	complex(trig_a.cos * hyp_b.cosh, // cos(a)*cosh(b)
				- (trig_a.sin * hyp_b.sinh) // -sin(a)*sinh(b)
			       );
	}
}
