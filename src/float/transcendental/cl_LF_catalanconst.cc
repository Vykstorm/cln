// catalanconst().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F_tran.h"


// Implementation.

#include "cln/lfloat.h"
#include "cl_LF_tran.h"
#include "cl_LF.h"
#include "cln/integer.h"
#include "cl_alloca.h"

namespace cln {

const cl_LF compute_catalanconst_ramanujan (uintC len)
{
	// [Jonathan M. Borwein, Peter B. Borwein: Pi and the AGM.
	//  Wiley 1987. Section 11.3, exercise 16 g, p. 386]
	// G = 3/8 * sum(n=0..infty, n!^2 / (2n+1)!*(2n+1))
	//     + pi/8 * log(2+sqrt(3)).
	// Every summand gives 0.6 new decimal digits in precision.
	// The sum is best evaluated using fixed-point arithmetic,
	// so that the precision is reduced for the later summands.
	var uintL actuallen = len + 2; // 2 Schutz-Digits
	var sintL scale = intDsize*actuallen;
	var cl_I sum = 0;
	var cl_I n = 0;
	var cl_I factor = ash(1,scale);
	while (!zerop(factor)) {
		sum = sum + truncate1(factor,2*n+1);
		n = n+1;
		factor = truncate1(factor*n,2*(2*n+1));
	}
	var cl_LF fsum = scale_float(cl_I_to_LF(sum,actuallen),-scale);
	var cl_LF g =
	  scale_float(The(cl_LF)(3*fsum)
	              + The(cl_LF)(pi(actuallen))
	                * ln(cl_I_to_LF(2,actuallen)+sqrt(cl_I_to_LF(3,actuallen))),
	              -3);
	return shorten(g,len); // verkürzen und fertig
}
// Bit complexity (N := len): O(N^2).

const cl_LF compute_catalanconst_ramanujan_fast (uintC len)
{
	// Same formula as above, using a binary splitting evaluation.
	// See [Borwein, Borwein, section 10.2.3].
	var uintL actuallen = len + 2; // 2 Schutz-Digits
	// Evaluate a sum(0 <= n < N, a(n)/b(n) * (p(0)...p(n))/(q(0)...q(n)))
	// with appropriate N, and
	//   a(n) = 1, b(n) = 2*n+1,
	//   p(n) = n for n>0, q(n) = 2*(2*n+1) for n>0.
	var uintL N = (intDsize/2)*actuallen;
	// 4^-N <= 2^(-intDsize*actuallen).
	CL_ALLOCA_STACK;
	var cl_I* bv = (cl_I*) cl_alloca(N*sizeof(cl_I));
	var cl_I* pv = (cl_I*) cl_alloca(N*sizeof(cl_I));
	var cl_I* qv = (cl_I*) cl_alloca(N*sizeof(cl_I));
	var uintL n;
	init1(cl_I, bv[0]) (1);
	init1(cl_I, pv[0]) (1);
	init1(cl_I, qv[0]) (1);
	for (n = 1; n < N; n++) {
		init1(cl_I, bv[n]) (2*n+1);
		init1(cl_I, pv[n]) (n);
		init1(cl_I, qv[n]) (2*(2*n+1));
	}
	var cl_pqb_series series;
	series.bv = bv;
	series.pv = pv; series.qv = qv; series.qsv = NULL;
	var cl_LF fsum = eval_rational_series(N,series,actuallen);
	for (n = 0; n < N; n++) {
		bv[n].~cl_I();
		pv[n].~cl_I();
		qv[n].~cl_I();
	}
	var cl_LF g =
	  scale_float(The(cl_LF)(3*fsum)
	              + The(cl_LF)(pi(actuallen))
	                * ln(cl_I_to_LF(2,actuallen)+sqrt(cl_I_to_LF(3,actuallen))),
	              -3);
	return shorten(g,len); // verkürzen und fertig
}
// Bit complexity (N := len): O(log(N)^2*M(N)).

const cl_LF compute_catalanconst_expintegral1 (uintC len)
{
	// We compute f(x) classically and g(x) using the partial sums of f(x).
	var uintC actuallen = len+2; // 2 Schutz-Digits
	var uintL x = (uintL)(0.693148*intDsize*actuallen)+1;
	var uintL N = (uintL)(2.718281828*x);
	var cl_LF fterm = cl_I_to_LF(1,actuallen);
	var cl_LF fsum = fterm;
	var cl_LF gterm = fterm;
	var cl_LF gsum = gterm;
	var uintL n;
	// After n loops
	//   fterm = x^n/n!, fsum = 1 + x/1! + ... + x^n/n!,
	//   gterm = S_n*x^n/n!, gsum = S_0*x^0/0! + ... + S_n*x^n/n!.
	for (n = 1; n < N; n++) {
		fterm = The(cl_LF)(fterm*x)/n;
		fsum = fsum + fterm;
		gterm = The(cl_LF)(gterm*x)/n;
		if (evenp(n))
			gterm = gterm + fterm/square((cl_I)(2*n+1));
		else
			gterm = gterm - fterm/square((cl_I)(2*n+1));
		gsum = gsum + gterm;
	}
	var cl_LF result = gsum/fsum;
	return shorten(result,len); // verkürzen und fertig
}
// Bit complexity (N = len): O(N^2).

// Same algorithm as expintegral1, but using binary splitting to evaluate
// the sums.
const cl_LF compute_catalanconst_expintegral2 (uintC len)
{
	var uintC actuallen = len+2; // 2 Schutz-Digits
	var uintL x = (uintL)(0.693148*intDsize*actuallen)+1;
	var uintL N = (uintL)(2.718281828*x);
	CL_ALLOCA_STACK;
	var cl_pqd_series_term* args = (cl_pqd_series_term*) cl_alloca(N*sizeof(cl_pqd_series_term));
	var uintL n;
	for (n = 0; n < N; n++) {
		if (n==0) {
			init1(cl_I, args[n].p) (1);
			init1(cl_I, args[n].q) (1);
		} else {
			init1(cl_I, args[n].p) (x);
			init1(cl_I, args[n].q) (n);
		}
		init1(cl_I, args[n].d) (evenp(n)
		                        ? square((cl_I)(2*n+1))
		                        : -square((cl_I)(2*n+1)));
	}
	var cl_LF result = eval_pqd_series(N,args,actuallen);
	for (n = 0; n < N; n++) {
		args[n].p.~cl_I();
		args[n].q.~cl_I();
		args[n].d.~cl_I();
	}
	return shorten(result,len); // verkürzen und fertig
}
// Bit complexity (N = len): O(log(N)^2*M(N)).

// Using Cohen-Villegas-Zagier acceleration, but without binary splitting.
const cl_LF compute_catalanconst_cvz1 (uintC len)
{
	var uintC actuallen = len+2; // 2 Schutz-Digits
	var uintL N = (uintL)(0.39321985*intDsize*actuallen)+1;
#if 0
	var cl_LF fterm = cl_I_to_LF(2*(cl_I)N*(cl_I)N,actuallen);
	var cl_LF fsum = fterm;
	var cl_LF gterm = fterm;
	var cl_LF gsum = gterm;
	var uintL n;
	// After n loops
	//   fterm = (N+n)!N/(2n+2)!(N-n-1)!*2^(2n+2), fsum = ... + fterm,
	//   gterm = S_n*fterm, gsum = ... + gterm.
	for (n = 1; n < N; n++) {
		fterm = The(cl_LF)(fterm*(2*(cl_I)(N-n)*(cl_I)(N+n)))/((cl_I)(2*n+1)*(cl_I)(n+1));
		fsum = fsum + fterm;
		gterm = The(cl_LF)(gterm*(2*(cl_I)(N-n)*(cl_I)(N+n)))/((cl_I)(2*n+1)*(cl_I)(n+1));
		if (evenp(n))
			gterm = gterm + fterm/square((cl_I)(2*n+1));
		else
			gterm = gterm - fterm/square((cl_I)(2*n+1));
		gsum = gsum + gterm;
	}
	var cl_LF result = gsum/(cl_I_to_LF(1,actuallen)+fsum);
#else
	// Take advantage of the fact that fterm and fsum are integers.
	var cl_I fterm = 2*(cl_I)N*(cl_I)N;
	var cl_I fsum = fterm;
	var cl_LF gterm = cl_I_to_LF(fterm,actuallen);
	var cl_LF gsum = gterm;
	var uintL n;
	// After n loops
	//   fterm = (N+n)!N/(2n+2)!(N-n-1)!*2^(2n+2), fsum = ... + fterm,
	//   gterm = S_n*fterm, gsum = ... + gterm.
	for (n = 1; n < N; n++) {
		fterm = exquopos(fterm*(2*(cl_I)(N-n)*(cl_I)(N+n)),(cl_I)(2*n+1)*(cl_I)(n+1));
		fsum = fsum + fterm;
		gterm = The(cl_LF)(gterm*(2*(cl_I)(N-n)*(cl_I)(N+n)))/((cl_I)(2*n+1)*(cl_I)(n+1));
		if (evenp(n))
			gterm = gterm + cl_I_to_LF(fterm,actuallen)/square((cl_I)(2*n+1));
		else
			gterm = gterm - cl_I_to_LF(fterm,actuallen)/square((cl_I)(2*n+1));
		gsum = gsum + gterm;
	}
	var cl_LF result = gsum/cl_I_to_LF(1+fsum,actuallen);
#endif
	return shorten(result,len); // verkürzen und fertig
}
// Bit complexity (N = len): O(N^2).

// Using Cohen-Villegas-Zagier acceleration, with binary splitting.
const cl_LF compute_catalanconst_cvz2 (uintC len)
{
	var uintC actuallen = len+2; // 2 Schutz-Digits
	var uintL N = (uintL)(0.39321985*intDsize*actuallen)+1;
	CL_ALLOCA_STACK;
	var cl_pqd_series_term* args = (cl_pqd_series_term*) cl_alloca(N*sizeof(cl_pqd_series_term));
	var uintL n;
	for (n = 0; n < N; n++) {
		init1(cl_I, args[n].p) (2*(cl_I)(N-n)*(cl_I)(N+n));
		init1(cl_I, args[n].q) ((cl_I)(2*n+1)*(cl_I)(n+1));
		init1(cl_I, args[n].d) (evenp(n)
		                        ? square((cl_I)(2*n+1))
		                        : -square((cl_I)(2*n+1)));
	}
	var cl_pqd_series_result sums;
	eval_pqd_series_aux(N,args,sums);
	// Here we need U/(1+S) = V/D(Q+T).
	var cl_LF result =
	  cl_I_to_LF(sums.V,actuallen) / The(cl_LF)(sums.D * cl_I_to_LF(sums.Q+sums.T,actuallen));
	for (n = 0; n < N; n++) {
		args[n].p.~cl_I();
		args[n].q.~cl_I();
		args[n].d.~cl_I();
	}
	return shorten(result,len); // verkürzen und fertig
}
// Bit complexity (N = len): O(log(N)^2*M(N)).

// Timings of the above algorithms, on an i486 33 MHz, running Linux.
//    N      ram    ramfast  exp1    exp2    cvz1    cvz2
//    10     0.055   0.068   0.32    0.91    0.076   0.11
//    25     0.17    0.26    0.95    3.78    0.23    0.43
//    50     0.43    0.73    2.81   11.5     0.63    1.36
//   100     1.32    2.24    8.82   34.1     1.90    4.48
//   250     6.60   10.4    48.7   127.5    10.3    20.8
//   500    24.0    30.9   186     329      38.4    58.6
//  1000    83.0    89.0   944     860     149     163
//  2500   446     352    6964    3096    1032     545
//  5000  1547     899
// asymp.    N^2     FAST    N^2     FAST    N^2     FAST
// (FAST means O(log(N)^2*M(N)))
//
// The "exp1" and "exp2" algorithms are always about 10 to 15 times slower
// than the "ram" and "ramfast" algorithms.
// The break-even point between "ram" and "ramfast" is at about N = 1410.

const cl_LF compute_catalanconst (uintC len)
{
	if (len >= 1410)
		return compute_catalanconst_ramanujan_fast(len);
	else
		return compute_catalanconst_ramanujan(len);
}
// Bit complexity (N := len): O(log(N)^2*M(N)).

const cl_LF catalanconst (uintC len)
{
	var uintC oldlen = TheLfloat(cl_LF_catalanconst)->len; // vorhandene Länge
	if (len < oldlen)
		return shorten(cl_LF_catalanconst,len);
	if (len == oldlen)
		return cl_LF_catalanconst;

	// TheLfloat(cl_LF_catalanconst)->len um mindestens einen konstanten Faktor
	// > 1 wachsen lassen, damit es nicht zu häufig nachberechnet wird:
	var uintC newlen = len;
	oldlen += floor(oldlen,2); // oldlen * 3/2
	if (newlen < oldlen)
		newlen = oldlen;

	// gewünschte > vorhandene Länge -> muß nachberechnen:
	cl_LF_catalanconst = compute_catalanconst(newlen);
	return (len < newlen ? shorten(cl_LF_catalanconst,len) : cl_LF_catalanconst);
}

}  // namespace cln
