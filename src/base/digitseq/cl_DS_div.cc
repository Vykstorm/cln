// cl_UDS_divide().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_DS.h"


// Implementation.

#include "cl_N.h"
#include "cl_abort.h"

// We observe the following timings:
// Time for dividing 2*N digits by N digits, on a i486 33 MHz running Linux:
//      N   standard  Newton
//      10    0.0003  0.0012
//      25    0.0013  0.0044
//      50    0.0047  0.0125
//     100    0.017   0.037
//     250    0.108   0.146
//     500    0.43    0.44
//    1000    1.72    1.32
//    2500   11.2     4.1
//    5000   44.3     9.5
//   10000  187      20.6
//   -----> Newton faster for N >= 550.
// Time for dividing 3*N digits by N digits, on a i486 33 MHz running Linux:
//      N   standard  Newton
//      10    0.0006  0.0025
//      25    0.0026  0.0103
//      50    0.0092  0.030
//     100    0.035   0.089
//     250    0.215   0.362
//     500    0.85    1.10
//    1000    3.44    3.21
//    2500   23.3     7.9
//    5000   89.0    15.6
//   10000  362      33.1
//   -----> Newton faster for N >= 740.
// Time for dividing m digits by n digits:
//   n = 2,3,5,10,25,50,100,250: Newton never faster.
//   n = 400: Newton faster for m >= 440, m < 600
//   n = 500: Newton faster for m >= 530, m < 900
//   n = 600: Newton faster for m >= 630, m < 1250
//   n = 700: Newton faster for m >= 730, m < 1530
//   n = 800: Newton faster for m >= 825, m < 2600 or m >= 5300
//   n = 900: Newton faster for m >= 925, m < 2700 or m >= 3400
//   n = 1000: Newton faster for m >= 1020
//   n = 1500: Newton faster for m >= 1520
//   n = 2000: Newton faster for m >= 2020
//   n = 2500: Newton faster for m >= 2520
//   n = 5000: Newton faster for m >= 5020
// Break-even-point. When in doubt, prefer to choose the standard algorithm.
  static inline cl_boolean cl_recip_suitable (uintL m, uintL n) // m > n
    { if (n < 500)
        return cl_false;
      else
        if (n < 1000)
          return (cl_boolean)((m >= n+30) && (m < 3*n-600));
        else
          return (cl_boolean)(m >= n+20);
    }

// Dividiert zwei Unsigned Digit sequences durcheinander.
// UDS_divide(a_MSDptr,a_len,a_LSDptr, b_MSDptr,b_len,b_LSDptr, &q,&r);
// Die UDS a = a_MSDptr/a_len/a_LSDptr (a>=0) wird durch
// die UDS b = b_MSDptr/b_len/b_LSDptr (b>=0) dividiert:
// a = q * b + r mit 0 <= r < b. Bei b=0 Error.
// q der Quotient, r der Rest.
// q = q_MSDptr/q_len/q_LSDptr, r = r_MSDptr/r_len/r_LSDptr beides
// Normalized Unsigned Digit sequences.
// Vorsicht: q_LSDptr <= r_MSDptr,
//           Vorzeichenerweiterung von r kann q zerstören!
//           Vorzeichenerweiterung von q ist erlaubt.
// a und b werden nicht modifiziert.
//
// Methode:
// erst a und b normalisieren: a=[a[m-1],...,a[0]], b=[b[n-1],...,b[0]]
// mit m>=0 und n>0 (Stellensystem der Basis beta=2^intDsize).
// Falls m<n, ist q:=0 und r:=a.
// Falls m>=n=1, Single-Precision-Division:
//   r:=0, j:=m,
//   while j>0 do
//     {Hier (q[m-1]*beta^(m-1)+...+q[j]*beta^j) * b[0] + r*beta^j =
//           = a[m-1]*beta^(m-1)+...+a[j]*beta^j und 0<=r<b[0]<beta}
//     j:=j-1, r:=r*beta+a[j], q[j]:=floor(r/b[0]), r:=r-b[0]*q[j].
//   Normalisiere [q[m-1],...,q[0]], liefert q.
// Falls m>=n>1, Multiple-Precision-Division:
//   Es gilt a/b < beta^(m-n+1).
//   s:=intDsize-1-(Nummer des höchsten Bits in b[n-1]), 0<=s<intDsize.
//   Schiebe a und b um s Bits nach links und kopiere sie dabei. r:=a.
//   r=[r[m],...,r[0]], b=[b[n-1],...,b[0]] mit b[n-1]>=beta/2.
//   Für j=m-n,...,0: {Hier 0 <= r < b*beta^(j+1).}
//     Berechne q* :
//       q* := floor((r[j+n]*beta+r[j+n-1])/b[n-1]).
//       Bei Überlauf (q* >= beta) setze q* := beta-1.
//       Berechne c2 := ((r[j+n]*beta+r[j+n-1]) - q* * b[n-1])*beta + r[j+n-2]
//       und c3 := b[n-2] * q*.
//       {Es ist 0 <= c2 < 2*beta^2, sogar 0 <= c2 < beta^2 falls kein
//        Überlauf aufgetreten war. Ferner 0 <= c3 < beta^2.
//        Bei Überlauf und r[j+n]*beta+r[j+n-1] - q* * b[n-1] >= beta,
//        das heißt c2 >= beta^2, kann man die nächste Abfrage überspringen.}
//       Solange c3 > c2, {hier 0 <= c2 < c3 < beta^2} setze
//         q* := q* - 1, c2 := c2 + b[n-1]*beta, c3 := c3 - b[n-2].
//       Falls q* > 0:
//         Setze r := r - b * q* * beta^j, im einzelnen:
//           [r[n+j],...,r[j]] := [r[n+j],...,r[j]] - q* * [b[n-1],...,b[0]].
//           also: u:=0, for i:=0 to n-1 do
//                         u := u + q* * b[i],
//                         r[j+i]:=r[j+i]-(u mod beta) (+ beta, falls Carry),
//                         u:=u div beta (+ 1, falls bei der Subtraktion Carry)
//                 r[n+j]:=r[n+j]-u.
//           {Da stets u = (q* * [b[i-1],...,b[0]] div beta^i) + 1
//                       < q* + 1 <= beta, läuft der Übertrag u nicht über.}
//         Tritt dabei ein negativer Übertrag auf, so setze q* := q* - 1
//           und [r[n+j],...,r[j]] := [r[n+j],...,r[j]] + [0,b[n-1],...,b[0]].
//     Setze q[j] := q*.
//   Normalisiere [q[m-n],..,q[0]] und erhalte den Quotienten q,
//   Schiebe [r[n-1],...,r[0]] um s Bits nach rechts, normalisiere und
//   erhalte den Rest r.
//   Dabei kann q[j] auf dem Platz von r[n+j] liegen.
  void cl_UDS_divide (const uintD* a_MSDptr, uintC a_len, const uintD* a_LSDptr,
                      const uintD* b_MSDptr, uintC b_len, const uintD* b_LSDptr,
                      uintD* roomptr, // ab roomptr kommen a_len+1 freie Digits
                      DS* q_, DS* r_)
    { // a normalisieren (a_MSDptr erhöhen, a_len erniedrigen):
      while ((a_len>0) && (mspref(a_MSDptr,0)==0)) { msshrink(a_MSDptr); a_len--; }
      // b normalisieren (b_MSDptr erhöhen, b_len erniedrigen):
      loop
        { if (b_len==0) { cl_error_division_by_0(); }
          if (mspref(b_MSDptr,0)==0) { msshrink(b_MSDptr); b_len--; }
          else break;
        }
      // jetzt m=a_len >=0 und n=b_len >0.
      if (a_len < b_len)
        // m<n: Trivialfall, q=0, r:= Kopie von a.
        { var uintD* r_MSDptr = roomptr;
          var uintD* r_LSDptr = roomptr mspop a_len;
          // Speicheraufbau: r_MSDptr/0/r_MSDptr/a_len/r_LSDptr
          //                    |     q    |       r      |
          copy_loop_lsp(a_LSDptr,r_LSDptr,a_len);
          q_->MSDptr = r_MSDptr; q_->len = 0; q_->LSDptr = r_MSDptr; // q = 0, eine NUDS
          r_->MSDptr = r_MSDptr; r_->len = a_len; r_->LSDptr = r_LSDptr; // r = Kopie von a, eine NUDS
          return;
        }
      elif (b_len==1)
        // n=1: Single-Precision-Division
        { // beta^(m-1) <= a < beta^m  ==>  beta^(m-2) <= a/b < beta^m
          var uintD* q_MSDptr = roomptr;
          var uintD* q_LSDptr = q_MSDptr mspop a_len;
          var uintD* r_MSDptr = q_LSDptr;
          var uintD* r_LSDptr = r_MSDptr mspop 1;
          // Speicheraufbau: q_MSDptr/a_len/q_LSDptr    r_MSDptr/1/r_LSDptr
          //                     |      q      |           |     r    |
         {var uintD rest = divucopy_loop_msp(mspref(b_MSDptr,0),a_MSDptr,q_MSDptr,a_len); // Division durch b[0]
          var uintC r_len;
          if (!(rest==0))
            { mspref(r_MSDptr,0) = rest; r_len=1; } // Rest als r ablegen
            else
            { r_MSDptr = r_LSDptr; r_len=0; } // Rest auf 0 normalisieren
          if (mspref(q_MSDptr,0)==0)
            { msshrink(q_MSDptr); a_len--; } // q normalisieren
          q_->MSDptr = q_MSDptr; q_->len = a_len; q_->LSDptr = q_LSDptr; // q ablegen
          r_->MSDptr = r_MSDptr; r_->len = r_len; r_->LSDptr = r_LSDptr; // r ablegen
          return;
        }}
      else
        // n>1: Multiple-Precision-Division
        { // beta^(m-1) <= a < beta^m, beta^(n-1) <= b < beta^n  ==>
          // beta^(m-n-1) <= a/b < beta^(m-n+1).
          var uintL s;
          CL_ALLOCA_STACK;
          // s bestimmen:
          { var uintD msd = mspref(b_MSDptr,0); // b[n-1]
            #if 0
            s = 0;
            while ((sintD)msd >= 0) { msd = msd<<1; s++; }
            #else // ein wenig effizienter, Abfrage auf s=0 vorwegnehmen
            if ((sintD)msd < 0)
              { s = 0; goto shift_ok; }
              else
              { integerlengthD(msd, s = intDsize - ); goto shift; }
            #endif
          }
          // 0 <= s < intDsize.
          // Kopiere b und schiebe es dabei um s Bits nach links:
          if (!(s==0))
            shift:
            { var uintD* new_b_MSDptr;
              var uintD* new_b_LSDptr;
              num_stack_alloc(b_len,new_b_MSDptr=,new_b_LSDptr=);
              shiftleftcopy_loop_lsp(b_LSDptr,new_b_LSDptr,b_len,s);
              b_MSDptr = new_b_MSDptr; b_LSDptr = new_b_LSDptr;
            }
          shift_ok:
          // Wieder b = b_MSDptr/b_len/b_LSDptr.
          // Kopiere a und schiebe es dabei um s Bits nach links, erhalte r:
         {var uintD* r_MSDptr = roomptr;
          var uintD* r_LSDptr = roomptr mspop (a_len+1);
          // Speicheraufbau:  r_MSDptr/          a_len+1           /r_LSDptr
          //                     |                  r                  |
          // später:          q_MSDptr/a_len-b_len+1/r_MSDptr/b_len/r_LSDptr
          //                     |           q          |       r      |
          if (s==0)
            { copy_loop_lsp(a_LSDptr,r_LSDptr,a_len); mspref(r_MSDptr,0) = 0; }
            else
            { mspref(r_MSDptr,0) = shiftleftcopy_loop_lsp(a_LSDptr,r_LSDptr,a_len,s); }
          // Nun r = r_MSDptr/a_len+1/r_LSDptr.
          var uintC j = a_len-b_len; // m-n
          var uintD* q_MSDptr = r_MSDptr;
          var uintC q_len = j+1; // q wird m-n+1 Digits haben
          if (cl_recip_suitable(a_len,b_len))
            { // Bestimme Kehrwert c von b.
              var uintD* c_MSDptr;
              var uintD* c_LSDptr;
              num_stack_alloc(j+3,c_MSDptr=,c_LSDptr=);
              cl_UDS_recip(b_MSDptr,b_len,c_MSDptr,j+1);
              // c hat j+3 Digits, | beta^(m+2)/b - c | < beta.
              // Mit a' = floor(a/beta^n) multiplizieren, liefert d':
              var uintD* d_MSDptr;
              UDS_UDS_mul_UDS(j+1,r_MSDptr mspop (j+1), j+3,c_MSDptr mspop (j+3),
                              d_MSDptr=,,);
              // d' has 2*j+4 digits, d := floor(d'/beta^(j+2)) has j+2 digits.
              // | beta^(m+2)/b - c | < beta  ==> (since a < beta^(m+1))
              // | beta^(m+2)*a/b - a*c | < beta^(m+2),
              // 0 <= a - a'*beta^n < beta^n ==> (since c <= 2*beta^(j+2))
              // 0 <= a*c - a'*c*beta^n < 2*beta^(m+2) ==>
              // -beta^(m+2) < beta^(m+2)*a/b - a'*c*beta^n < 3*beta^(m+2) ==>
              // -1 < a/b - a'*c*beta^(-j-2) < 3 ==>
              // -1 < a/b - d'*beta^(-j-2) < 3,
              // -1 < d'*beta^(-j-2) - d <= 0 ==>
              // -2 < a/b - d < 3 ==>
              // -2 <= q - d < 3 ==> |q-d| <= 2.
              var uintD* d_LSDptr = d_MSDptr mspop (j+2);
              // Zur Bestimmung des Restes wieder mit b multiplizieren:
              var uintD* p_MSDptr;
              var uintD* p_LSDptr;
              UDS_UDS_mul_UDS(j+2,d_LSDptr, b_len,b_LSDptr, p_MSDptr=,,p_LSDptr=);
              // d ist um höchstens 2 zu groß, muß also evtl. zweimal um 1
              // decrementieren, bis das Produkt <= a wird.
              if ((mspref(p_MSDptr,0) > 0) || (compare_loop_msp(p_MSDptr mspop 1,r_MSDptr,a_len+1) > 0))
                { dec_loop_lsp(d_LSDptr,j+2);
                  if (subfrom_loop_lsp(b_LSDptr,p_LSDptr,b_len))
                    dec_loop_lsp(p_LSDptr lspop b_len,j+2);
                  if ((mspref(p_MSDptr,0) > 0) || (compare_loop_msp(p_MSDptr mspop 1,r_MSDptr,a_len+1) > 0))
                    { dec_loop_lsp(d_LSDptr,j+2);
                      if (subfrom_loop_lsp(b_LSDptr,p_LSDptr,b_len))
                        dec_loop_lsp(p_LSDptr lspop b_len,j+2);
                      if ((mspref(p_MSDptr,0) > 0) || (compare_loop_msp(p_MSDptr mspop 1,r_MSDptr,a_len+1) > 0))
                        cl_abort();
                }   }
              // Rest bestimmen:
              subfrom_loop_lsp(p_LSDptr,r_LSDptr,a_len+1);
              if (test_loop_msp(r_MSDptr,j)) cl_abort();
              r_MSDptr = r_LSDptr lspop b_len; // = r_MSDptr mspop (j+1);
              // d ist um höchstens 2 zu klein, muß also evtl. zweimal um 1
              // incrementieren, bis der Rest < b wird.
              if ((lspref(r_MSDptr,0) > 0) || (compare_loop_msp(r_MSDptr,b_MSDptr,b_len) >= 0))
                { inc_loop_lsp(d_LSDptr,j+2);
                  if (subfrom_loop_lsp(b_LSDptr,r_LSDptr,b_len))
                    lspref(r_LSDptr,b_len) -= 1;
                  if ((lspref(r_MSDptr,0) > 0) || (compare_loop_msp(r_MSDptr,b_MSDptr,b_len) >= 0))
                    { inc_loop_lsp(d_LSDptr,j+2);
                      if (subfrom_loop_lsp(b_LSDptr,r_LSDptr,b_len))
                        lspref(r_LSDptr,b_len) -= 1;
                      if ((lspref(r_MSDptr,0) > 0) || (compare_loop_msp(r_MSDptr,b_MSDptr,b_len) >= 0))
                        cl_abort();
                }   }
              // r ist fertig, q := d.
              if (mspref(d_MSDptr,0) > 0) cl_abort();
              q_len = j+1; copy_loop_msp(d_MSDptr mspop 1,q_MSDptr,q_len);
            }
            else
            { var uintD* r_ptr = r_LSDptr lspop j; // Pointer oberhalb von r[j]
              j = j+1;
              var uintD b_msd = mspref(b_MSDptr,0); // b[n-1]
              var uintD b_2msd = mspref(b_MSDptr,1); // b[n-2]
              #if HAVE_DD
              var uintDD b_msdd = highlowDD(b_msd,b_2msd); // b[n-1]*beta+b[n-2]
              #endif
              // Divisions-Schleife: (wird m-n+1 mal durchlaufen)
              // j = Herabzähler, b_MSDptr/b_len/b_LSDptr = [b[n-1],...,b[0]], b_len=n,
              // r_MSDptr = Pointer auf r[n+j] = Pointer auf q[j],
              // r_ptr = Pointer oberhalb von r[j].
              do { var uintD q_stern;
                   var uintD c1;
                   if (mspref(r_MSDptr,0) < b_msd) // r[j+n] < b[n-1] ?
                     { // Dividiere r[j+n]*beta+r[j+n-1] durch b[n-1], ohne Überlauf:
                       #if HAVE_DD
                         divuD(highlowDD(mspref(r_MSDptr,0),mspref(r_MSDptr,1)),b_msd, q_stern=,c1=);
                       #else
                         divuD(mspref(r_MSDptr,0),mspref(r_MSDptr,1),b_msd, q_stern=,c1=);
                       #endif
                     }
                     else
                     { // Überlauf, also r[j+n]*beta+r[j+n-1] >= beta*b[n-1]
                       q_stern = bitm(intDsize)-1; // q* = beta-1
                       // Teste ob r[j+n]*beta+r[j+n-1] - (beta-1)*b[n-1] >= beta
                       // <==> r[j+n]*beta+r[j+n-1] + b[n-1] >= beta*b[n-1]+beta
                       // <==> b[n-1] < floor((r[j+n]*beta+r[j+n-1]+b[n-1])/beta) {<= beta !} ist.
                       // Wenn ja, direkt zur Subtraktionschleife.
                       // (Andernfalls ist r[j+n]*beta+r[j+n-1] - (beta-1)*b[n-1] < beta
                       //  <==> floor((r[j+n]*beta+r[j+n-1]+b[n-1])/beta) = b[n-1] ).
                       if ((mspref(r_MSDptr,0) > b_msd) || ((c1 = mspref(r_MSDptr,1)+b_msd) < b_msd))
                         // r[j+n] >= b[n-1]+1 oder
                         // r[j+n] = b[n-1] und Addition r[j+n-1]+b[n-1] gibt Carry ?
                         { goto subtract; } // ja -> direkt in die Subtraktion
                     }
                   // q_stern = q*,
                   // c1 = (r[j+n]*beta+r[j+n-1]) - q* * b[n-1] (>=0, <beta).
                   #if HAVE_DD
                     { var uintDD c2 = highlowDD(c1,mspref(r_MSDptr,2)); // c1*beta+r[j+n-2]
                       var uintDD c3 = muluD(b_2msd,q_stern); // b[n-2] * q*
                       // Solange c2 < c3, c2 erhöhen, c3 erniedrigen:
                       // Rechne dabei mit c3-c2:
                       // solange >0, um b[n-1]*beta+b[n-2] erniedrigen.
                       // Dies kann wegen b[n-1]*beta+b[n-2] >= beta^2/2
                       // höchstens zwei mal auftreten.
                       if (c3 > c2)
                         { q_stern = q_stern-1; // q* := q* - 1
                           if (c3-c2 > b_msdd)
                             { q_stern = q_stern-1; } // q* := q* - 1
                     }   }
                   #else
                     // Wie oben, nur mit zweigeteilten c2=[c2hi|c2lo] und c3=[c3hi|c3lo]:
                     #define c2hi c1
                     { var uintD c2lo = mspref(r_MSDptr,2); // c2hi*beta+c2lo = c1*beta+r[j+n-2]
                       var uintD c3hi;
                       var uintD c3lo;
                       muluD(b_2msd,q_stern, c3hi=,c3lo=); // c3hi*beta+c3lo = b[n-2] * q*
                       if ((c3hi > c2hi) || ((c3hi == c2hi) && (c3lo > c2lo)))
                         { q_stern = q_stern-1; // q* := q* - 1
                           c3hi -= c2hi; if (c3lo < c2lo) { c3hi--; }; c3lo -= c2lo; // c3 := c3-c2
                           if ((c3hi > b_msd) || ((c3hi == b_msd) && (c3lo > b_2msd)))
                             { q_stern = q_stern-1; } // q* := q* - 1
                     }   }
                     #undef c2hi
                   #endif
                   if (!(q_stern==0))
                     subtract:
                     { // Subtraktionsschleife: r := r - b * q* * beta^j
                       var uintD carry = mulusub_loop_lsp(q_stern,b_LSDptr,r_ptr,b_len);
                       // Noch r_ptr[-b_len-1] -= carry, d.h. r_MSDptr[0] -= carry
                       // durchführen und danach r_MSDptr[0] vergessen:
                       if (carry > mspref(r_MSDptr,0))
                         // Subtraktion ergab Übertrag
                         { q_stern = q_stern-1; // q* := q* - 1
                           addto_loop_lsp(b_LSDptr,r_ptr,b_len); // Additionsschleife
                           // r[n+j] samt Carry kann vergessen werden...
                     }   }
                   // Berechnung von q* ist fertig.
                   msprefnext(r_MSDptr) = q_stern; // als q[j] ablegen
                   r_ptr = r_ptr mspop 1;
                 }
                 until (--j == 0);
            }
          // Nun ist q = [q[m-n],..,q[0]] = q_MSDptr/q_len/r_MSDptr
          // und r = [r[n-1],...,r[0]] = r_MSDptr/b_len/r_LSDptr.
          // q normalisieren und ablegen:
          if (mspref(q_MSDptr,0)==0)
            { msshrink(q_MSDptr); q_len--; }
          q_->MSDptr = q_MSDptr; q_->len = q_len; q_->LSDptr = r_MSDptr;
          // Schiebe [r[n-1],...,r[0]] um s Bits nach rechts:
          if (!(s==0))
            { shiftright_loop_msp(r_MSDptr,b_len,s); }
          // r normalisieren und ablegen:
          while ((b_len>0) && (mspref(r_MSDptr,0)==0))
            { msshrink(r_MSDptr); b_len--; }
          r_->MSDptr = r_MSDptr; r_->len = b_len; r_->LSDptr = r_LSDptr;
          return;
        }}
    }
// Bit complexity (N = a_len): O(M(N)).

