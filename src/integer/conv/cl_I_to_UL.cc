// cl_I_to_UL().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cln/number.h"
#include "cl_I.h"
#include "cl_DS.h"
#include "cln/io.h"
#include "cln/integer_io.h"
#include "cln/abort.h"

namespace cln {

uint32 cl_I_to_UL (const cl_I& obj)
{
	if (fixnump(obj)) {
		// Fixnum
		var sint32 wert = FN_to_L(obj);
		if (wert >= 0)
			return (uint32)wert;
		goto bad;
	} else { // Bignum
		var cl_heap_bignum* bn = TheBignum(obj);
		var uintC len = bn->length;
		if ((sintD)mspref(arrayMSDptr(bn->data,len),0) < 0)
			goto bad;
		#define IF_LENGTH(i)  \
		  if (bn_minlength <= i) /* genau i Digits überhaupt möglich? */\
		    if (len == i) /* genau i Digits? */				\
		      /* 2^((i-1)*intDsize-1) <= obj < 2^(i*intDsize-1) */	\
		      if ( (i*intDsize-1 > 32)					\
		           && ( ((i-1)*intDsize-1 >= 32)			\
		                || (mspref(arrayMSDptr(bn->data,len),0) >= (uintD)bitc(32-(i-1)*intDsize)) \
		         )    )							\
		        goto bad;						\
			else
		IF_LENGTH(1)
			return get_uint1D_Dptr(arrayLSDptr(bn->data,1));
		IF_LENGTH(2)
			return get_uint2D_Dptr(arrayLSDptr(bn->data,2));
		IF_LENGTH(3)
			return get_uint3D_Dptr(arrayLSDptr(bn->data,3));
		IF_LENGTH(4)
			return get_uint4D_Dptr(arrayLSDptr(bn->data,4));
		IF_LENGTH(5)
			return get_uint4D_Dptr(arrayLSDptr(bn->data,5));
		#undef IF_LENGTH
	}
	bad: // unpassendes Objekt
	fprint(std::cerr, "Not a 32-bit integer: ");
	fprint(std::cerr, obj);
	fprint(std::cerr, "\n");
	cl_abort();
}

}  // namespace cln
