// mkf_extract().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I_byte.h"


// Implementation.

#include "cl_integer.h"
#include "cl_I.h"
#include "cl_DS.h"

const cl_I mkf_extract (const cl_I& x, uintL p, uintL q)
{
      CL_ALLOCA_STACK;
      var const uintD* MSDptr;
      var uintC len;
      var const uintD* LSDptr;
      I_to_NDS_nocopy(x, MSDptr=,len=,LSDptr=,cl_true, { return 0; } ); // NDS zu x bilden
      // MSDptr erhöhen und len erniedrigen, so daß len = ceiling(q/intDsize) wird:
      { var uintL qD = ceiling(q,intDsize); // ceiling(q/intDsize)
        // wegen q<=l ist qD = ceiling(q/intDsize) <= ceiling((l+1)/intDsize) = len, also
        // paßt qD ebenso wie len in ein uintC.
        MSDptr = MSDptr mspop ((uintL)len - qD); // MSDptr um len-qD Digits erhöhen
        len = qD; // len um len-qD erniedrigen
      }
      // Platz (len Digits) für die neue UDS bereitstellen:
      var uintD* newMSDptr;
      num_stack_alloc_1((uintL)len, newMSDptr = ,); // Platz belegen
      {var uintL pD = p/intDsize; // floor(p/intDsize), paßt in ein uintC
       // Kopiere len-pD Digits aus der DS zu x heraus:
       var uintD* midptr = copy_loop_msp(MSDptr,newMSDptr,len-(uintC)pD);
       // Lösche p-intDsize*floor(p/intDsize) Bits im Digit unterhalb von midptr:
       {var uintL p_D = p%intDsize;
        if (!(p_D==0)) { lspref(midptr,0) &= minus_bit(p_D); }
       }
       // Lösche pD Digits darüber:
       clear_loop_msp(midptr,pD);
      }
      // Lösche intDsize*ceiling(q/intDsize)-q Bits im ersten Digit:
      {var uintL q_D = q%intDsize;
       if (!(q_D==0))
         { mspref(newMSDptr,0) &= (uintD)((1L<<q_D)-1); } // intDsize-q_D Bits löschen
      }
      // Jetzt enthält die UDS newMSDptr/len/.. die extrahierten Bits.
      return UDS_to_I(newMSDptr,len);
}
