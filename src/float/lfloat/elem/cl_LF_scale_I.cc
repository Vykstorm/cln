// scale_float().

// General includes.
#include "base/cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "float/lfloat/cl_LF.h"
#include "float/lfloat/cl_LF_impl.h"
#include "float/cl_F.h"
#include "integer/cl_I.h"

namespace cln {

const cl_LF scale_float (const cl_LF& x, const cl_I& delta)
{
  // Methode:
  // delta=0 -> x als Ergebnis
  // x=0.0 -> x als Ergebnis
  // delta muß ein Integer betragsmäßig <= LF_exp_high-LF_exp_low sein.
  // Neues LF mit um delta vergrößertem Exponenten bilden.
      if (eq(delta,0)) { return x; } // delta=0 -> x als Ergebnis
      var uintE uexp = TheLfloat(x)->expo;
      if (uexp==0) { return x; }
      var uintE udelta;
      // |delta| muß <= LF_exp_high-LF_exp_low < 2^32 sein. Wie bei I_to_UL:
	if (fixnump(delta)) {
		// Fixnum
		var sintV sdelta = FN_to_V(delta);
		if (sdelta >= 0)
			{ udelta = sdelta; goto pos; }
		else
			{ udelta = sdelta; goto neg; }
	} else {
	    // Bignum
	    var cl_heap_bignum* bn = TheBignum(delta);
	    if ((sintD)mspref(arrayMSDptr(bn->data,bn->length),0) >= 0) {
		#define IF_LENGTH(i)  \
		  if (bn_minlength <= i) /* genau i Digits überhaupt möglich? */\
		    if (bn->length == i) /* genau i Digits? */			\
		      /* 2^((i-1)*intDsize-1) <= delta < 2^(i*intDsize-1) */	\
		      if ( (i*intDsize-1 > 32)					\
		           && ( ((i-1)*intDsize-1 >= 32)			\
		                || (mspref(arrayMSDptr(bn->data,i),0) >= (uintD)bitc(32-(i-1)*intDsize)) \
		         )    )							\
		        goto overflow;						\
			else
		IF_LENGTH(1)
			{ udelta = get_uint1D_Dptr(arrayLSDptr(bn->data,1)); goto pos; }
		IF_LENGTH(2)
			{ udelta = get_uint2D_Dptr(arrayLSDptr(bn->data,2)); goto pos; }
		IF_LENGTH(3)
			{ udelta = get_uint3D_Dptr(arrayLSDptr(bn->data,3)); goto pos; }
		IF_LENGTH(4)
			{ udelta = get_uint4D_Dptr(arrayLSDptr(bn->data,4)); goto pos; }
		IF_LENGTH(5)
			{ udelta = get_uint4D_Dptr(arrayLSDptr(bn->data,5)); goto pos; }
		#undef IF_LENGTH
		goto overflow; // delta zu groß
	    } else {
		#define IF_LENGTH(i)  \
		  if (bn_minlength <= i) /* genau i Digits überhaupt möglich? */\
		    if (bn->length == i) /* genau i Digits? */			\
		      /* - 2^((i-1)*intDsize-1) > delta >= - 2^(i*intDsize-1) */\
		      if ( (i*intDsize-1 > 32)					\
		           && ( ((i-1)*intDsize-1 >= 32)			\
		                || (mspref(arrayMSDptr(bn->data,i),0) < (uintD)(-bitc(32-(i-1)*intDsize))) \
		         )    )							\
		        goto underflow;						\
			else
		IF_LENGTH(1)
			{ udelta = get_sint1D_Dptr(arrayLSDptr(bn->data,1)); goto pos; }
		IF_LENGTH(2)
			{ udelta = get_sint2D_Dptr(arrayLSDptr(bn->data,2)); goto pos; }
		IF_LENGTH(3)
			{ udelta = get_sint3D_Dptr(arrayLSDptr(bn->data,3)); goto pos; }
		IF_LENGTH(4)
			{ udelta = get_sint4D_Dptr(arrayLSDptr(bn->data,4)); goto pos; }
		IF_LENGTH(5)
			{ udelta = get_sint4D_Dptr(arrayLSDptr(bn->data,5)); goto pos; }
		#undef IF_LENGTH
		goto underflow; // delta zu klein
	    }
	}

      pos: // udelta = delta >=0
	if (   ((uexp = uexp+udelta) < udelta) // Exponent-Überlauf?
	    || (uexp > LF_exp_high) // oder Exponent zu groß?
	   )
	  overflow:
	  { throw floating_point_overflow_exception(); }
	goto ok;

      neg: // delta <0, udelta = 2^32+delta
	if (   ((uexp = uexp+udelta) >= udelta) // oder Exponent-Unterlauf?
	    || (uexp < LF_exp_low) // oder Exponent zu klein?
	   )
	  underflow:
	  { throw floating_point_underflow_exception(); }
	goto ok;

      ok:
        var uintC len = TheLfloat(x)->len;
        return encode_LFu(TheLfloat(x)->sign,uexp,arrayMSDptr(TheLfloat(x)->data,len),len);
}

}  // namespace cln
