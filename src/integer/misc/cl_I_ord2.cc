// ord2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"

// Methode 1a:
//   Sei n = ord2(x). Dann ist logxor(x,x-1) = 2^n + (2^n-1) = 2^(n+1)-1.
//   Also  (ord2 x) = (1- (integer-length (logxor x (1- x)))) .
// Methode 1b:
//   Sei n = ord2(x). Dann ist logand(x,-x) = 2^n.
//   Also  (ord2 x) = (1- (integer-length (logand x (- x)))) .
// Methode 1c:
//   Sei n = ord2(x). Dann ist lognot(logior(x,-x)) = 2^n-1.
//   Also  (ord2 x) = (integer-length (lognot (logior x (- x)))) .
// Methode 2:
//   Nullbits am Schluﬂ von x abz‰hlen:
//   (ord2 x) = intDsize * Anzahl der Nulldigits am Schluﬂ
//              + Anzahl der Nullbits am Ende des letzten Digits /=0.

uintL ord2 (const cl_I& x) // x /= 0
{
	if (fixnump(x))
	  { var uint32 x_ = FN_to_L(x); // x als 32-Bit-Zahl
	    ord2_32(x_,return);
	  }
	  else
	  { var uintL bitcount = 0;
	    var const uintD* ptr;
	    BN_to_NDS_nocopy(x, ,,ptr=); // normalisierte DS zu x bilden.
	    while (lspref(ptr,0) == 0) { lsshrink(ptr); bitcount += intDsize; } // Nulldigits abz‰hlen
	    var uintD lsd = lspref(ptr,0); // letztes Digit /=0
	    ord2_D(lsd,bitcount +=); // dessen Nullbits abz‰hlen
	    return bitcount;
          }
}
