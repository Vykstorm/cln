// decode_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat.h"


// Implementation.

#include "cl_LF.h"
#include "cl_LF_impl.h"
#include "cl_I.h"

const cl_decoded_lfloat decode_float (const cl_LF& x)
{
	// x entpacken:
	var cl_signean sign;
	var sintL exp;
	var uintC mantlen;
	var const uintD* mantMSDptr;
	LF_decode(x, { return cl_decoded_lfloat(x, 0, encode_LF1(mantlen)); },
		     sign=,exp=,mantMSDptr=,mantlen=,);
	return cl_decoded_lfloat(
		encode_LFu(0,0+LF_exp_mid,mantMSDptr,mantlen), // (-1)^0 * 2^0 * m erzeugen
		L_to_I(exp), // e als Fixnum
		encode_LF1s(sign,mantlen) // (-1)^s erzeugen
	       );
}
