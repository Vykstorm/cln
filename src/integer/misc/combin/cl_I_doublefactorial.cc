// doublefactorial().

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_I_doublefactorial)

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_I_combin.h"

  // Method:
  // n <= 19 -> Get result (Fixnum) from table
  // Else:
  //   odd n:  same procedure as factorial(n) but now, each odd number in
  //     n/2^k < m <= n/2^(k-1) occurs only once in the product and we do not
  //     shift at the end, since there are no powers of two.
  //   even n: set m to n/2 and calculate n!!=factorial(m)*2^m using the same
  //     divide and conquer method as in the function factorial() to compute
  //     the product of all odd numbers.  At the end, apply a shift of
  //     ord2(n!) = n - logcount(n) to account both for 2^m and for powers of
  //     two in factorial(m).

static cl_I const doublefakul_table [] = {
        L_to_FN(1),
        L_to_FN(1UL),
        L_to_FN(1UL*2),
        L_to_FN(1UL*3),
        #if (cl_value_len>=5)
        L_to_FN(1UL*2*4),
        L_to_FN(1UL*3*5),
        #if (cl_value_len>=7)
        L_to_FN(1UL*2*4*6),
        #if (cl_value_len>=8)
        L_to_FN(1UL*3*5*7),
        #if (cl_value_len>=10)
        L_to_FN(1UL*2*4*6*8),
        #if (cl_value_len>=11)
        L_to_FN(1UL*3*5*7*9),
        #if (cl_value_len>=13)
        L_to_FN(1UL*2*4*6*8*10),
        #if (cl_value_len>=15)
        L_to_FN(1UL*3*5*7*9*11),
        #if (cl_value_len>=17)
        L_to_FN(1UL*2*4*6*8*10*12),
        #if (cl_value_len>=19)
        L_to_FN(1UL*3*5*7*9*11*13),
        #if (cl_value_len>=21)
        L_to_FN(1UL*2*4*6*8*10*12*14),
        #if (cl_value_len>=22)
        L_to_FN(1UL*3*5*7*9*11*13*15),
        #if (cl_value_len>=25)
        L_to_FN(1UL*2*4*6*8*10*12*14*16),
        #if (cl_value_len>=27)
        L_to_FN(1UL*3*5*7*9*11*13*15*17),
        #if (cl_value_len>=29)
        L_to_FN(1UL*2*4*6*8*10*12*14*16*18),
        #if (cl_value_len>=31)
        L_to_FN(1UL*3*5*7*9*11*13*15*17*19),
        #if (cl_value_len>=33)
        ...
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
};

const cl_I doublefactorial (uintL n) // assume n >= 0 small
{
      if (n < sizeof(doublefakul_table)/sizeof(cl_I))
        { return doublefakul_table[n]; }
        else {
        if (n%2)  // n odd
          { var cl_I prod = 1; // bisheriges Produkt := 1
            var uintL k = 1;
            var uintL A = n;
            var uintL B = n; // obere Intervallgrenze floor(n/2^(k-1))
            loop
              { // 'A' enthält floor(n/2^(k-1)).
                A = A >> 1; // untere Grenze floor(n/2^k)
                // 'A' enthält floor(n/2^k).
                // Bilde Teilprodukt prod(A < i <= B & oddp(i), i)
                //       = prod(floor((A-1)/2) < i <= floor((B-1)/2), 2*i+1)
                // wobei B = floor(n/2^(k-1)), A = floor(n/2^k) = floor(B/2).
                { var uintL b = floor(B-1,2);
                  if (b==0) break; // B=2 oder B=1 -> Produkt fertig
                  var uintL a = floor(A-1,2);
                  prod = cl_I_prod_ungerade(a,b) * prod; // aufmultiplizieren
                }
                k = k+1;
                B = A;
              }
            return prod;
          } else  // n even
          { var cl_I prod = 1; // bisheriges Produkt := 1
            var uintL m = n/2;
            var uintL k = 1;
            var uintL A = m;
            var uintL B = m; // obere Intervallgrenze floor(m/2^(k-1))
            loop
              { // 'A' enthält floor(m/2^(k-1)).
                A = A >> 1; // untere Grenze floor(m/2^k)
                // 'A' enthält floor(m/2^k).
                // Bilde Teilprodukt prod(A < i <= B & oddp(i), i)
                //       = prod(floor((A-1)/2) < i <= floor((B-1)/2), 2*i+1)
                // wobei B = floor(m/2^(k-1)), A = floor(m/2^k) = floor(B/2).
                { var uintL b = floor(B-1,2);
                  if (b==0) break; // B=2 oder B=1 -> Produkt fertig
                  var uintL a = floor(A-1,2);
                  prod = expt_pos(cl_I_prod_ungerade(a,b),k) * prod; // aufmultiplizieren
                }
                k = k+1;
                B = A;
              }
            return prod << (n - logcount(n));
          }
        }
}
// Bit complexity (N := n): O(log(N)^2*M(N)).

CL_PROVIDE_END(cl_I_doublefactorial)

