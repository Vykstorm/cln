// cl_UDS_mul().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_DS.h"


// Implementation.

#include "cl_low.h"
#include "cl_malloc.h"
#include "cl_abort.h"

// Multiplikations-Doppelschleife:
// Multipliziert zwei UDS und legt das Ergebnis in einer dritten UDS ab.
// cl_UDS_mul(sourceptr1,len1,sourceptr2,len2,destptr);
// multipliziert die UDS  sourceptr1[-len1..-1]  (len1>0)
//           mit der UDS  sourceptr2[-len1..-1]  (len2>0)
// und legt das Ergebnis in der UDS  destptr[-len..-1]  (len=len1+len2) ab.
// Unterhalb von destptr werden len Digits Platz benötigt.
  void cl_UDS_mul (const uintD* sourceptr1, uintC len1,
                   const uintD* sourceptr2, uintC len2,
                   uintD* destptr);
// Spezialfall sourceptr1 == sourceptr2 && len1 == len2.
  void cl_UDS_mul_square (const uintD* sourceptr, uintC len,
                          uintD* destptr);

// Multiplikation nach Schulmethode:
  static inline void mulu_2loop (const uintD* sourceptr1, uintC len1,
                                 const uintD* sourceptr2, uintC len2,
                                 uintD* destptr)
  { // Es ist 2 <= len1 <= len2.
    // Erster Schleifendurchlauf:
    mulu_loop_lsp(lsprefnext(sourceptr1),sourceptr2,destptr,len2);
    lsshrink(destptr);
    var uintD* destptr2 = destptr lspop len2;
    // äußere Schleife läuft über source1 :
    dotimespC(len1,len1-1,
      { // innere Schleife läuft über source2 :
        var uintD carry =
          muluadd_loop_lsp(lsprefnext(sourceptr1),sourceptr2,destptr,len2);
        lsprefnext(destptr2) = carry; // UDS um das Carry-Digit verlängern
        lsshrink(destptr);
      });
  }
  static inline void mulu_2loop_square (const uintD* sourceptr, uintC len,
                                        uintD* destptr)
  { // Es ist 2 <= len.
    // Gemischte Produkte:
    #if 0
    // 2*(  x[1] * x[0..0] * b^1
    //    + x[2] * x[1..0] * b^2
    //    + ...
    //    + x[n-1] * x[n-2..0]*b^(n-1))
    { var const uintD* sourceptr1 = sourceptr lspop 1;
      var uintD* destptr1 = destptr;
      lsprefnext(destptr1) = 0;
      var uintD* destptr2 = destptr1;
      var uintC count;
      for (count = 1; count < len; count++)
        { // sourceptr1 = sourceptr lspop count, destptr1 = destptr lspop count,
          // destptr2 = destptr lspop (2*count-1).
          lsprefnext(destptr2) = 0;
          var uintD carry =
            muluadd_loop_lsp(lsprefnext(sourceptr1),sourceptr,destptr1,count);
          lsprefnext(destptr2) = carry;
          destptr1 = destptr1 lspop 1;
        }
      { var uintD carry = shift1left_loop_lsp(destptr lspop 1,2*len-2);
        lspref(destptr2,0) = (carry==0 ? 0 : 1);
    } }
    #else
    // 2*(  x[n-1..1] * x[0] * b^1
    //    + x[n-1..2] * x[1] * b^3
    //    + ...
    //    + x[n-1..n-1] * x[n-2] * b^(2*n-3))
    { var const uintD* sourceptr1 = sourceptr;
      var uintD* destptr2 = destptr;
      lsprefnext(destptr2) = 0;
      var uintC count = len-1;
      { var uintD digit = lsprefnext(sourceptr1);
        mulu_loop_lsp(digit,sourceptr1,destptr2,count);
      }
      var uintD* destptr1 = destptr lspop (len+1);
      while (--count > 0)
        { destptr2 = destptr2 lspop 2;
          var uintD digit = lsprefnext(sourceptr1);
          var uintD carry = muluadd_loop_lsp(digit,sourceptr1,destptr2,count);
          lsprefnext(destptr1) = carry;
        }
      { var uintD carry = shift1left_loop_lsp(destptr lspop 1,2*len-2);
        lspref(destptr1,0) = (carry==0 ? 0 : 1);
    } }
    #endif
    // Quadrate:
    len = 2*len;
    do { len -= 2;
         var uintD digit = lsprefnext(sourceptr);
         #if HAVE_DD
         var uintDD prod = muluD(digit,digit);
         var uintDD accu = highlowDD(lspref(destptr,1),lspref(destptr,0));
         accu += prod;
         lspref(destptr,0) = lowD(accu); lspref(destptr,1) = highD(accu);
         destptr = destptr lspop 2;
         if (accu < prod) { inc_loop_lsp(destptr,len); }
         #else
         var uintD hi;
         var uintD lo;
         muluD(digit,digit, hi=,lo=);
         var uintD tmp;
         tmp = lspref(destptr,0) + lo; lspref(destptr,0) = tmp;
         if (tmp < lo) hi++;
         tmp = lspref(destptr,1) + hi; lspref(destptr,1) = tmp;
         destptr = destptr lspop 2;
         if (tmp < hi) { inc_loop_lsp(destptr,len); }
         #endif
       } while (len > 0);
  }

// Karatsuba-Multiplikation: O(n^(log 3 / log 2))
  static void mulu_karatsuba (const uintD* sourceptr1, uintC len1,
                              const uintD* sourceptr2, uintC len2,
                              uintD* destptr);
  static void mulu_karatsuba_square (const uintD* sourceptr, uintC len,
                                     uintD* destptr);
#include "cl_DS_mul_kara.h"
  // karatsuba_threshold = Länge, ab der die Karatsuba-Multiplikation bevorzugt
  // wird. Der Break-Even-Point bestimmt sich aus Zeitmessungen.
  // Als Test dient (progn (time (! 5000)) nil), das viele kleine und einige
  // ganz große Multiplikationen durchführt. Miß die Runtime.
  // Unter Linux mit einem 80486:      Auf einer Sparc 2:
  // threshold  time in 0.01 sec.
  //      5        125   127
  //      6        116   117
  //      7        107   110
  //      8        101   103
  //      9         99   102
  //     10         98   100
  //     11         97   100
  //     12         96    99
  //     13         97    99
  //     14         97   100
  //     15         97    99
  //     16         98   100
  //     17         98   100
  //     18         98   100
  //     19         98   101
  //     20         99   102
  //     25        103   105
  //     30        109   111
  //     40        115   118
  //     50        122   125
  //     70        132   134
  //    100        151   152
  //    150        164   167
  //    250        183   187
  //    500        203   205
  //   1000        203   205
  //             (clisp)(cln)
  // Das Optimum scheint bei karatsuba_threshold = 12 zu liegen.
  // Da das Optimum aber vom Verhältnis
  //         Zeit für uintD-Multiplikation / Zeit für uintD-Addition
  // abhängt und die gemessenen Zeiten auf eine Unterschreitung des Optimums
  // empfindlicher reagieren als auf eine Überschreitung des Optimums,
  // sind wir vorsichtig und wählen einen Wert etwas über dem Optimum:
  const unsigned int cl_karatsuba_threshold = 16;

#if 0 // Lohnt sich nicht

// FFT-Multiplikation nach Nussbaumer: O(n log n log log n)
#include "cl_DS_mul_nuss.h"
  // nuss_threshold = Länge, ab der die Nussbaumer-Multiplikation bevorzugt
  // wird. Der Break-Even-Point bestimmt sich aus Zeitmessungen.
  // Multiplikation zweier N-Wort-Zahlen unter Linux mit einem 80486:
  //    N     kara   nuss  nuss-asm  (time in sec.)
  //   1000    0.36   1.05   0.70
  //   5000    4.69  10.0    6.71
  //  25000   61.6   62.7   40.2
  //  32500   91.8   62.7   40.3
  //  35000  102.7  124.7   80.4
  //  50000  185    132     85.2
  int cl_nuss_threshold = 1000000;

// FFT-Multiplikation in Z/pZ: O(n log n log log n)
#include "cl_DS_mul_fftp.h"
  // fftp_threshold = Länge, ab der die FFT-Multiplikation mod p bevorzugt
  // wird. Der Break-Even-Point bestimmt sich aus Zeitmessungen.
  // Multiplikation zweier N-Wort-Zahlen unter Linux mit einem 80486:
  //    N     kara   fftp  (time in sec.)
  //   1000    0.36   1.57
  //   5000    4.66  14.86
  //  25000   61.1   75.0
  //  32500   90.8   75.5
  //  35000  101.6  150.1
  //  50000  183    160
  int cl_fftp_threshold = 1000000;

// FFT-Multiplikation in Z/pZ: O(n log n log log n)
// für drei verschiedene Primzahlen p1,p2,p3 < 2^32.
#include "cl_DS_mul_fftp3.h"
  // fftp3_threshold = Länge, ab der die FFT-Multiplikation mod p_i bevorzugt
  // wird. Der Break-Even-Point bestimmt sich aus Zeitmessungen.
  // Multiplikation zweier N-Wort-Zahlen unter Linux mit einem 80486:
  //    N     kara   fftp3  fftp  (time in sec.)
  //   1000    0.36   0.59   1.57
  //   5000    4.66   5.44  14.89
  //  10000   13.98  11.91  32.43
  //  25000   61.1   27.4   75.4
  //  32500   90.5   28.1   75.5
  //  35000  101.4   54.8  150.4
  //  50000  183     58.9  161.6
  int cl_fftp3_threshold = 1000000;

// FFT-Multiplikation in Z/pZ: O(n log n log log n)
// für drei verschiedene Primzahlen p1,p2,p3 < 2^32,
// mit Montgomery-Multiplikation.
#include "cl_DS_mul_fftp3m.h"
  // fftp3_threshold = Länge, ab der die FFT-Multiplikation mod p_i bevorzugt
  // wird. Der Break-Even-Point bestimmt sich aus Zeitmessungen.
  // Multiplikation zweier N-Wort-Zahlen unter
  // Linux mit einem 80486, 33 MHz, mit Benutzung der GMP-Low-Level-Funktionen:
  //    N     kara    fftm  fftp3m  fftp3  fftp  (time in sec.)
  //   1000    0.35   0.49   0.54   0.59   1.58
  //   2500    1.48   0.97   2.34   2.52   6.99
  //   5000    4.43   2.19   5.08   5.48  15.16
  //  10000   13.33   4.68  10.93  11.82  32.94
  //  25000   58.5   12.0   25.3   27.4   77.0
  //  32500   86.0   25.0   26.1   28.0   77.3
  //  35000   96.5   25.0   50.8   54.9  152.8
  //  50000  176     25.2   54.2   58.5  163.4
  // und auf einer SPARC 20 mit 75 MHz, ohne GMP-Low-Level-Funktionen:
  //    N     kara    fftm  fftp3m  fftp3  fftp  (time in sec.)
  //   1000    0.076  0.096  0.113  0.233  0.415
  //   2500    0.32   0.21   0.48   1.03   1.82
  //   5000    0.97   0.51   1.03   2.22   3.96
  //  10000    2.99   1.03   2.23   4.72   8.59
  //  25000   13.22   2.73   4.99  10.78  19.73
  //  32500   19.3    5.7    5.2   10.9   19.7
  //  35000   21.5    5.9   10.0   21.7   39.4
  //  50000   39.5    6.0   11.3   23.1   42.7
  int cl_fftp3m_threshold = 1000000;

#endif

// FFT-Multiplikation in Z/pZ: O(n^1.29)
#include "cl_DS_mul_fftm.h"
  // fftm_threshold = Länge, ab der die FFT-Multiplikation mod m bevorzugt
  // wird. Der Break-Even-Point bestimmt sich aus Zeitmessungen.
  // Multiplikation zweier N-Wort-Zahlen unter
  //  Linux mit einem 80486:               Solaris, Sparc 10/20:
  //    N     kara   fftm  (time in sec.)    kara   fftm
  //   1000    0.36   0.54                    0.08   0.10
  //   5000    4.66   2.48                    1.01   0.51
  //  25000   61.1   13.22                   13.23   2.73
  //  32500   91.0   27.5                    20.0    5.8
  //  35000  102.1   27.5                    21.5    5.6
  //  50000  183     27.6                    40.7    5.6
  // Multiplikation zweier N-Wort-Zahlen unter
  //  Linux mit einem 80486:               Solaris, Sparc 10/20:
  //    N     kara   fftm  (time in sec.)    kara   fftm
  //   1000    0.36   0.54                    0.08   0.10
  //   1260    0.52   0.50                    0.11   0.10
  //   1590    0.79   0.51                    0.16   0.10
  //   2000    1.09   1.07                    0.23   0.21
  //   2520    1.57   1.08                    0.33   0.21
  //   3180    2.32   1.08                    0.50   0.21
  //   4000    3.29   2.22                    0.70   0.41
  //   5040    4.74   2.44                    0.99   0.50
  //    N1    N2    kara   fftm  (time in sec.)    kara   fftm
  //   1250  1250    0.51   0.50                    0.11   0.10
  //   1250  1580    0.70   0.50                    0.15   0.10
  //   1250  2000    0.89   0.51                    0.18   0.10
  //   1250  2250    0.99   0.51                    0.21   0.10
  //   1250  2500    1.08   1.03     <---           0.22   0.21
  //   1250  2800    1.20   1.07                    0.26   0.21
  //   1250  3100    1.35   1.07                    0.28   0.21
  // Es gibt also noch Werte von (len1,len2) mit 1250 <= len1 <= len2, bei
  // denen "kara" schneller ist als "fftm", aber nicht viele und dort auch
  // nur um 5%. Darum wählen wir ab hier die FFT-Multiplikation.
  const unsigned int cl_fftm_threshold = 1250; // muß stets >= 6 sein (sonst Endlosrekursion!)
  // This is the threshold for multiplication of equally sized factors.
  // When the lengths differ much, the threshold varies:
  //   len2 = 3000   len1 >= 800
  //   len2 = 3500   len1 >= 700
  //   len2 = 4000   len1 >= 580
  //   len2 = 4500   len1 >= 430
  //   len2 = 5000   len1 >= 370
  //   len2 = 5500   len1 >= 320
  //   len2 = 6000   len1 >= 500
  //   len2 = 7000   len1 >= 370
  //   len2 = 8000   len1 >= 330
  //   len2 = 9000   len1 >= 420
  //   len2 =10000   len1 >= 370
  //   len2 =11000   len1 >= 330
  //   len2 =12000   len1 >= 330
  //   len2 =13000   len1 >= 350
  // Let's choose the following condition:
  const unsigned int cl_fftm_threshold1 = 330;
  const unsigned int cl_fftm_threshold2 = 2*cl_fftm_threshold;
  //   len1 > cl_fftm_threshold1 && len2 > cl_fftm_threshold2
  //   && len1 >= cl_fftm_threshold1 + cl_fftm_threshold/(len2-cl_fftm_threshold1)*(cl_fftm_threshold-cl_fftm_threshold1).
  static inline cl_boolean cl_fftm_suitable (uintL len1, uintL len2)
    { if (len1 >= cl_fftm_threshold)
        return cl_true;
      if (len1 > cl_fftm_threshold1)
        if (len2 > cl_fftm_threshold2)
          { var uint32 hi;
            var uint32 lo;
            mulu32(len1-cl_fftm_threshold1,len2-cl_fftm_threshold1, hi=,lo=);
            if (hi > 0 || lo >= cl_fftm_threshold*(cl_fftm_threshold-cl_fftm_threshold1))
              return cl_true;
          }
      return cl_false;
    }

#if 0 // Lohnt sich nicht

// FFT-Multiplikation über den komplexen Zahlen.
#include "cl_DS_mul_fftc.h"
  // Multiplikation zweier N-Wort-Zahlen unter
  //  Linux mit einem i486 33 MHz
  //    N     kara/fftm  fftc   fftclong
  //   1000      0.35     1.52     0.94
  //   2500      0.98     7.6/8.4  4.7
  //   5000      2.2     18.2     10.2
  //  10000      4.7     34       22
  // Multiplikation zweier N-Wort-Zahlen unter
  //  Linux mit einem i586 90/100 MHz
  //    N     kara/fftm  fftc   fftclong
  //   1000      0.03     0.20   0.16
  //   2500      0.16     1.6    0.92
  //   5000      0.3      2.6    2.2
  //  10000      0.7      7.1    4.8
  //  25000      1.6    (50MB)  20.7(22MB)
  // Multiplikation zweier N-Wort-Zahlen unter
  //  Solaris, Sparc 20, 75 MHz
  //    N     kara/fftm  fftc
  //   1000      0.07     0.14
  //   2500      0.21     0.76
  //   5000      0.44     1.75
  //  10000      0.88     4.95
  //  25000      2.3     (15MB)

// FFT-Multiplikation über den komplexen Zahlen, Symmetrie ausnutzend.
#include "cl_DS_mul_fftcs.h"
  // Multiplikation zweier N-Wort-Zahlen unter
  //  Linux mit einem i486 33 MHz
  //    N     kara/fftm  fftcs  fftcslong
  //   1000      0.34     0.71     0.43
  //   2500      0.98     3.4      2.1
  //   5000      2.2      8.0      4.7
  //  10000      4.7     16.1     10.4
  // Multiplikation zweier N-Wort-Zahlen unter
  //  Solaris, Sparc 20, 75 MHz
  //    N     kara/fftm  fftcs
  //    300      0.010    0.012
  //    400      0.018    0.027
  //    500      0.023    0.027
  //    600      0.031    0.027
  //    700      0.031    0.027
  //    800      0.051    0.058
  //    900      0.064    0.059
  //   1000      0.069    0.059
  //   1250      0.088    0.13
  //   1500      0.088    0.13
  //   1750      0.088    0.13
  //   2000      0.19     0.13
  //   2500      0.19     0.29
  //   3000      0.19     0.33
  //   3500      0.20     0.31
  //   4000      0.37     0.70
  //   4500      0.38     0.70
  //   5000      0.43     0.69
  //   6000      0.43     0.69
  //   7000      0.43     1.62
  //   8000      0.88     1.60
  //   9000      0.88     1.6
  //  10000      0.90     1.55
  //  12000      0.89     4.7
  //  14000      0.90     5.2
  //  16000      1.43     5.2

#endif

#if 0 // Keine gute Fehlerabschätzung

// FFT-Multiplikation über den komplexen Zahlen, mit reellen Zahlen rechnend.
#include "cl_DS_mul_fftr.h"
  // Multiplikation zweier N-Wort-Zahlen unter
  //  Linux mit einem i486 33 MHz
  //    N     kara/fftm  fftr   fftrlong
  //   1000      0.34     0.64     0.40
  //   2500      0.98     3.5      2.0
  //   5000      2.2      7.2/7.7  4.6
  //  10000      4.7     16.6     10.0

#endif

//  int cl_mul_algo = 0;
  void cl_UDS_mul (const uintD* sourceptr1, uintC len1,
                   const uintD* sourceptr2, uintC len2,
                   uintD* destptr)
    { // len1<=len2 erzwingen:
      if (len1>len2)
        {{var const uintD* temp;
          temp = sourceptr1; sourceptr1 = sourceptr2; sourceptr2 = temp;
         }
         {var uintC temp;
          temp = len1; len1 = len2; len2 = temp;
        }}
      if (len1==1)
        // nur eine Einfachschleife
        { mulu_loop_lsp(lsprefnext(sourceptr1),sourceptr2,destptr,len2); }
      else
        {
//          if (cl_mul_algo > 0)
//            mulu_fftcs(sourceptr1,len1,sourceptr2,len2,destptr);
//          else
//          if (cl_mul_algo > 0)
//            mulu_nussbaumer(sourceptr1,len1,sourceptr2,len2,destptr);
//          else
          if (len1 < cl_karatsuba_threshold)
            // Multiplikation nach Schulmethode
            mulu_2loop(sourceptr1,len1,sourceptr2,len2,destptr);
          else // len1 groß
          if (!cl_fftm_suitable(len1,len2))
            // Karatsuba-Multiplikation
            // (ausgelagert, um die eigentliche Multiplikationsfunktion nicht
            // durch zu viele Registervariablen zu belasten):
            mulu_karatsuba(sourceptr1,len1,sourceptr2,len2,destptr);
          else
            //mulu_fft_modp(sourceptr1,len1,sourceptr2,len2,destptr);
            //mulu_nussbaumer(sourceptr1,len1,sourceptr2,len2,destptr);
            //mulu_fft_modp3(sourceptr1,len1,sourceptr2,len2,destptr);
            mulu_fft_modm(sourceptr1,len1,sourceptr2,len2,destptr);
          #ifdef DEBUG_MUL_XXX
          { // Check the correctness of an other multiplication algorithm:
            CL_ALLOCA_STACK;
            var uintD tmpprod_xxx = cl_alloc_array(uintD,len1+len2);
            mulu_xxx(sourceptr1,len1,sourceptr2,len2,arrayLSDptr(tmpprod_xxx,len1+len2));
            if (compare_loop_msp(destptr lspop (len1+len2),arrayMSDptr(tmpprod_xxx,len1+len2),len1+len2))
              cl_abort();
          }
          #endif
        }
    }

// Special support for squaring.
// Squaring takes approximately 69% of the time of a normal multiplication.
  #include "cl_DS_mul_kara_sqr.h" // defines mulu_karatsuba_square()
  void cl_UDS_mul_square (const uintD* sourceptr, uintC len,
                          uintD* destptr)
  { if (len==1)
      { var uintD digit = lspref(sourceptr,0);
        #if HAVE_DD
        var uintDD prod = muluD(digit,digit);
        lspref(destptr,0) = lowD(prod); lspref(destptr,1) = highD(prod);
        #else
        muluD(digit,digit, lspref(destptr,1)=,lspref(destptr,0)=);
        #endif
      }
    else
      { if (len < cl_karatsuba_threshold)
          mulu_2loop_square(sourceptr,len,destptr);
        else
          if (!(len >= cl_fftm_threshold))
            mulu_karatsuba_square(sourceptr,len,destptr);
          else
            mulu_fft_modm(sourceptr,len,sourceptr,len,destptr);
      }
  }
