// scale_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_ffloat.h"


// Implementation.

#include "cl_FF.h"
#include "cl_F.h"
#include "cl_I.h"

const cl_FF scale_float (const cl_FF& x, const cl_I& delta)
{
  // Methode:
  // x=0.0 -> x als Ergebnis
  // delta muﬂ ein Fixnum betragsm‰ﬂig <= FF_exp_high-FF_exp_low sein.
  // Neues FF mit um delta vergrˆﬂertem Exponenten bilden.
      // x entpacken:
      var cl_signean sign;
      var sintL exp;
      var uint32 mant;
      FF_decode(x, { return x; }, sign=,exp=,mant=);
      if (!minusp(delta))
        // delta>=0
        { var uintL udelta;
          if (fixnump(delta)
              && ((udelta = FN_to_L(delta)) <= (uintL)(FF_exp_high-FF_exp_low))
             )
            { exp = exp+udelta;
              return encode_FF(sign,exp,mant);
            }
            else
            { cl_error_floating_point_overflow(); }
        }
        else
        // delta<0
        { var uintL udelta;
          if (fixnump(delta)
              && ((udelta = -FN_to_L(delta)) <= (uintL)(FF_exp_high-FF_exp_low))
              && ((cl_value_len+1<intLsize) || !(udelta==0))
             )
            { exp = exp-udelta;
              return encode_FF(sign,exp,mant);
            }
            else
            if (underflow_allowed())
              { cl_error_floating_point_underflow(); }
              else
              { return cl_FF_0; }
        }
}
