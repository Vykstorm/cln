// digits_to_I().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I.h"


// Implementation.

#include "cl_DS.h"

namespace cln {

const cl_I digits_to_I (const char * MSBptr, uintL len, uintD base)
{
      CL_ALLOCA_STACK;
      var uintD* erg_MSDptr;
      var uintC erg_len;
      var uintD* erg_LSDptr;
      // Platz f¸rs Ergebnis:
      // 1+ceiling(len*log(base)/(intDsize*log(2))) oder etwas mehr Digits
      var uintL need = 1+floor(len,intDsize*256); // > len/(intDsize*256) >=0
      switch (base) // need mit ceiling(256*log(base)/log(2)) multiplizieren:
        { case 2: need = 256*need; break;
          case 3: need = 406*need; break;
          case 4: need = 512*need; break;
          case 5: need = 595*need; break;
          case 6: need = 662*need; break;
          case 7: need = 719*need; break;
          case 8: need = 768*need; break;
          case 9: need = 812*need; break;
          case 10: need = 851*need; break;
          case 11: need = 886*need; break;
          case 12: need = 918*need; break;
          case 13: need = 948*need; break;
          case 14: need = 975*need; break;
          case 15: need = 1001*need; break;
          case 16: need = 1024*need; break;
          case 17: need = 1047*need; break;
          case 18: need = 1068*need; break;
          case 19: need = 1088*need; break;
          case 20: need = 1107*need; break;
          case 21: need = 1125*need; break;
          case 22: need = 1142*need; break;
          case 23: need = 1159*need; break;
          case 24: need = 1174*need; break;
          case 25: need = 1189*need; break;
          case 26: need = 1204*need; break;
          case 27: need = 1218*need; break;
          case 28: need = 1231*need; break;
          case 29: need = 1244*need; break;
          case 30: need = 1257*need; break;
          case 31: need = 1269*need; break;
          case 32: need = 1280*need; break;
          case 33: need = 1292*need; break;
          case 34: need = 1303*need; break;
          case 35: need = 1314*need; break;
          case 36: need = 1324*need; break;
          default: NOTREACHED
        }
      // Nun gilt need >= len*log(base)/(intDsize*log(2)).
      need += 1;
      num_stack_alloc(need,,erg_LSDptr=);
      erg_MSDptr = erg_LSDptr; erg_len = 0;
      // Ziffern einzeln draufaddieren:
      while (len > 0)
        { // erg_MSDptr/erg_len/erg_LSDptr ist eine NUDS, erg_len < need.
          var uintB ch = *(const uintB *)MSBptr; MSBptr++; // n‰chstes Character
          if (!(ch=='.')) // Punkt ¸berlesen
            { // Wert von ch ('0'-'9','A'-'Z','a'-'z') bilden:
              ch = ch - '0';
              if (ch > '9'-'0') // keine Ziffer?
                { ch = ch+'0'-'A'+10;
                  if (ch > 'Z'-'A'+10) // kein Groﬂbuchstabe?
                    { ch = ch+'A'-'a'; } // dann ein Kleinbuchstabe
                }
              // multipliziere erg mit base und addiere ch:
             {var uintD carry = mulusmall_loop_lsp(base,erg_LSDptr,erg_len,ch);
              if (!(carry==0))
                // muﬂ NUDS vergrˆﬂern:
                { lsprefnext(erg_MSDptr) = carry; erg_len++; }
            }}
          len--;
        }
      return NUDS_to_I(erg_MSDptr,erg_len);
}

}  // namespace cln
