// scale_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"
#include "cl_F.h"

namespace cln {

const cl_SF scale_float (const cl_SF& x, sintC delta)
{
  // Methode:
  // x=0.0 -> x als Ergebnis
  // delta muß betragsmäßig <= SF_exp_high-SF_exp_low sein.
  // Neues SF mit um delta vergrößertem Exponenten bilden.
      // x entpacken:
      var cl_signean sign;
      var sintL exp;
      var uint32 mant;
      SF_decode(x, { return x; }, sign=,exp=,mant=);
      if (delta >= 0)
        // delta>=0
        { var uintC udelta = delta;
          if (udelta <= (uintL)(SF_exp_high-SF_exp_low))
            { exp = exp+udelta;
              return encode_SF(sign,exp,mant);
            }
            else
            { cl_error_floating_point_overflow(); }
        }
        else
        // delta<0
        { var uintC udelta = -delta;
          if (udelta <= (uintL)(SF_exp_high-SF_exp_low))
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
