// unary operator -

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"

const cl_I operator- (const cl_I& x)
{
	if (fixnump(x)) {
		#if (cl_value_len < intLsize)
		return L_to_I(- FN_to_L(x));
		#elif (cl_word_size==64)
		return Q_to_I(- FN_to_Q(x));
		#else // (cl_value_len == intLsize)
		var sint32 xhi = sign_of(FN_to_L(x));
		var uint32 xlo = FN_to_L(x);
		return L2_to_I(-xhi-(xlo!=0),-xlo);
		#endif
	} else {
          // x Bignum
          CL_ALLOCA_STACK;
          var uintD* MSDptr;
          var uintC len;
          var uintD* LSDptr;
          BN_to_NDS_1(x, MSDptr=,len=,LSDptr=); // NDS zu x bilden, len>0
          // vorsorglich 1 Digit mehr belegen:
          { var sintD sign = sign_of_sintD(mspref(MSDptr,0));
            lsprefnext(MSDptr) = sign; len++;
          }
          // Negierschleife:
          neg_loop_lsp(LSDptr,len);
          // MSDigit ist nun = 0x0000 oder = 0xFFFF
          return DS_to_I(MSDptr,len); // DS wieder zum Integer machen
	}
}
