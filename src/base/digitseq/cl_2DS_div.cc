// div2adic().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_2DS.h"


// Implementation.

#include "cl_2D.h"
#include "cl_DS.h"
#include "cl_abort.h"

// Timings on a i486 33 MHz running Linux:
// Divide N digits by N digits          Divide 2*N digits by N digits
//     N   standard  Newton                 N   standard  Newton
//     10    0.00015 0.00054                10    0.00023 0.00054
//     25    0.00065 0.00256                25    0.00116 0.00256
//     50    0.0024  0.0083                 50    0.0044  0.0082
//    100    0.0089  0.027                 100    0.0172  0.027
//    250    0.054   0.130                 250    0.107   0.130
//    500    0.22    0.42                  500    0.425   0.42
//   1000    0.86    1.30                 1000    1.72    1.30
//   2500    5.6     4.1                  2500   11.0     4.1
//   5000   22.3     9.4                  5000   44.7     9.3
//  10000   91.2    20.6                 10000  182      20.5
//  -----> Newton faster for N >= 2070   -----> Newton faster for N >= 500
//
// 1.0*N / N : Newton for N >= 2070 or 1790 >= N >= 1460
// 1.1*N / N : Newton for N >= 1880 or 1790 >= N >= 1320
// 1.2*N / N : Newton for N >= 1250
// 1.3*N / N : Newton for N >= 1010
// 1.4*N / N : Newton for N >=  940
// 1.5*N / N : Newton for N >=  750
// 1.6*N / N : Newton for N >=  625
// 1.7*N / N : Newton for N >=  550
// 1.8*N / N : Newton for N >=  500
// 1.9*N / N : Newton for N >=  500
// 2.0*N / N : Newton for N >=  500
//
// Break-even-point. When in doubt, prefer to choose the standard algorithm.
  static inline cl_boolean cl_recip_suitable (uintL m, uintL n) // n <= m
    { if (n < 500)
        return cl_false;
      else // when n >= 2100/(m/n)^2, i.e. (m/46)^2 > n
        { var uintL mq = floor(m,46);
          if ((mq >= bit(16)) || ((uintL)(mq*mq) > n))
            return cl_true;
          else
            return cl_false;
        }
    }

void div2adic (uintC a_len, const uintD* a_LSDptr, uintC b_len, const uintD* b_LSDptr, uintD* dest_LSDptr)
{
  var uintC lendiff = a_len - b_len;
  if (cl_recip_suitable(a_len,b_len))
    { // Division using reciprocal (Newton-Hensel algorithm).
      CL_ALLOCA_STACK;
      // Bestimme Kehrwert c von b mod 2^(intDsize*b_len).
      var uintD* c_LSDptr;
      num_stack_alloc(b_len,,c_LSDptr=);
      recip2adic(b_len,b_LSDptr,c_LSDptr);
      // Bestimme q := a * c mod 2^(intDsize*b_len).
      var uintD* q_LSDptr;
      num_stack_alloc(2*b_len,,q_LSDptr=);
      cl_UDS_mul(a_LSDptr,b_len,c_LSDptr,b_len,q_LSDptr);
      // Zur Bestimmung des Restes wieder mit b multiplizieren:
      var uintD* p_LSDptr;
      num_stack_alloc(2*b_len,,p_LSDptr=);
      cl_UDS_mul(q_LSDptr,b_len,b_LSDptr,b_len,p_LSDptr);
      // Überprüfen, daß p == a mod 2^(intDsize*b_len):
      if (compare_loop_msp(a_LSDptr lspop b_len,p_LSDptr lspop b_len,b_len))
        cl_abort();
      // Quotient q und "Rest" (a-b*q)/2^(intDsize*b_len) ablegen:
      copy_loop_lsp(q_LSDptr,dest_LSDptr,b_len);
      if (lendiff <= b_len)
        { sub_loop_lsp(a_LSDptr lspop b_len,p_LSDptr lspop b_len,dest_LSDptr lspop b_len,lendiff); }
        else
        { var uintD carry = sub_loop_lsp(a_LSDptr lspop b_len,p_LSDptr lspop b_len,dest_LSDptr lspop b_len,b_len);
          copy_loop_lsp(a_LSDptr lspop 2*b_len,dest_LSDptr lspop 2*b_len,lendiff-b_len);
          if (carry) { dec_loop_lsp(dest_LSDptr lspop 2*b_len,lendiff-b_len); }
        }
    }
    else
    { // Standard division.
      var uintD b0inv = div2adic(1,lspref(b_LSDptr,0)); // b'
      copy_loop_lsp(a_LSDptr,dest_LSDptr,a_len); // d := a
      do { var uintD digit = lspref(dest_LSDptr,0); // nächstes d[j]
           digit = mul2adic(b0inv,digit);
           // digit = nächstes c[j]
           if (a_len <= b_len)
             { mulusub_loop_lsp(digit,b_LSDptr,dest_LSDptr,a_len); } // d := d - b * c[j] * beta^j
             else
             // a_len > b_len, b wird als durch Nullen fortgesetzt gedacht.
             { var uintD carry = mulusub_loop_lsp(digit,b_LSDptr,dest_LSDptr,b_len);
               if (lspref(dest_LSDptr,b_len) >= carry)
                 { lspref(dest_LSDptr,b_len) -= carry; }
               else
                 { lspref(dest_LSDptr,b_len) -= carry;
                   dec_loop_lsp(dest_LSDptr lspop (b_len+1),a_len-(b_len+1));
             }   }
           // Nun ist lspref(dest_LSDptr,0) = 0.
           lspref(dest_LSDptr,0) = digit; // c[j] ablegen
           lsshrink(dest_LSDptr); a_len--; // nächstes j
         }
         until (a_len==lendiff);
    }
}
// Bit complexity (N = max(a_len,b_len)): O(M(N)).

