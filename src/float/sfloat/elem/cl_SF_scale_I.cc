// scale_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"
#include "cl_F.h"
#include "cl_I.h"

namespace cln {

const cl_SF scale_float (const cl_SF& x, const cl_I& delta)
{
  // Methode:
  // x=0.0 -> x als Ergebnis
  // delta muﬂ ein Fixnum betragsm‰ﬂig <= SF_exp_high-SF_exp_low sein.
  // Neues SF mit um delta vergrˆﬂertem Exponenten bilden.
      // x entpacken:
      var cl_signean sign;
      var sintL exp;
      var uint32 mant;
      SF_decode(x, { return x; }, sign=,exp=,mant=);
      if (!minusp(delta))
        // delta>=0
        { var uintL udelta;
          if (fixnump(delta)
              && ((udelta = FN_to_L(delta)) <= (uintL)(SF_exp_high-SF_exp_low))
             )
            { exp = exp+udelta;
              return encode_SF(sign,exp,mant);
            }
            else
            { cl_error_floating_point_overflow(); }
        }
        else
        // delta<0
        { var uintL udelta;
          if (fixnump(delta)
              && ((udelta = -FN_to_L(delta)) <= (uintL)(SF_exp_high-SF_exp_low))
              && ((cl_value_len+1<intLsize) || !(udelta==0))
             )
            { exp = exp-udelta;
              return encode_SF(sign,exp,mant);
            }
            else
            if (underflow_allowed())
              { cl_error_floating_point_underflow(); }
              else
              { return SF_0; }
        }
}

}  // namespace cln
