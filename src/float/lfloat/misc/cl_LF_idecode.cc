// integer_decode_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"
#include "cl_I.h"
#include "cl_DS.h"

namespace cln {

MAYBE_INLINE
const cl_idecoded_float integer_decode_float (const cl_LF& x)
{
	// x entpacken:
	var uintL uexp = TheLfloat(x)->expo;
	if (uexp == 0)
		{ return cl_idecoded_float(0, 0, 1); }
	var cl_signean sign = TheLfloat(x)->sign;
	var uintC len = TheLfloat(x)->len;
	// intDsize*len >= 53 >= 33 >= cl_value_len, also len >= bn_minlength.
	// Baue Integer für die Mantisse.
	// Vorne 1 Nulldigit, damit es eine NDS wird.
	var Bignum mant = allocate_bignum(1+len);
	mspref(arrayMSDptr(TheBignum(mant)->data,1+len),0) = 0;
	copy_loop_msp(arrayMSDptr(TheLfloat(x)->data,len),arrayMSDptr(TheBignum(mant)->data,1+len) mspop 1,len); // NUDS kopieren
	return cl_idecoded_float(
		// Mantisse
		mant,
		// e-intDsize*n = uexp-LF_exp_mid-intDsize*n als Integer
		minus(uexp, LF_exp_mid + intDsize*len),
		(sign>=0 ? cl_I(1) : cl_I(-1)) // (-1)^s erzeugen
	       );
}

}  // namespace cln
