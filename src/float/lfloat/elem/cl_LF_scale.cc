// scale_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"
#include "cl_LF_impl.h"
#include "cl_F.h"

namespace cln {

const cl_LF scale_float (const cl_LF& x, sintL delta)
{
  // Methode:
  // delta=0 -> x als Ergebnis
  // x=0.0 -> x als Ergebnis
  // delta muﬂ ein Integer betragsm‰ﬂig <= LF_exp_high-LF_exp_low sein.
  // Neues LF mit um delta vergrˆﬂertem Exponenten bilden.
      if (delta == 0) { return x; } // delta=0 -> x als Ergebnis
      var uintL uexp = TheLfloat(x)->expo;
      if (uexp==0) { return x; }
      var uintL udelta = delta;
      if (delta >= 0) {
        // udelta = delta >=0
	if (   ((uexp = uexp+udelta) < udelta) // Exponent-‹berlauf?
	    || (uexp > LF_exp_high) // oder Exponent zu groﬂ?
	   )
	  { cl_error_floating_point_overflow(); }
      } else {
        // delta <0, udelta = 2^32+delta
	if (   ((uexp = uexp+udelta) >= udelta) // oder Exponent-Unterlauf?
	    || (uexp < LF_exp_low) // oder Exponent zu klein?
	   )
	  { cl_error_floating_point_underflow(); }
      }
      var uintC len = TheLfloat(x)->len;
      return encode_LFu(TheLfloat(x)->sign,uexp,arrayMSDptr(TheLfloat(x)->data,len),len);
}

}  // namespace cln
