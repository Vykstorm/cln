// cl_exp_aux().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F_tran.h"


// Implementation.

#include "cl_lfloat.h"
#include "cl_LF_tran.h"
#include "cl_LF.h"
#include "cl_integer.h"
#include "cl_alloca.h"
#include "cl_abort.h"

#undef floor
#include <math.h>
#define floor cln_floor

const cl_LF cl_exp_aux (const cl_I& p, uintL lq, uintC len)
{
 {	Mutable(cl_I,p);
	var uintL lp = integer_length(p); // now |p| < 2^lp.
	if (!(lp <= lq)) cl_abort();
	lp = lq - lp; // now |p/2^lq| < 2^-lp.
	// Minimize lq (saves computation time).
	{
		var uintL lp2 = ord2(p);
		if (lp2 > 0) {
			p = p >> lp2;
			lq = lq - lp2;
		}
	}
	// Evaluate a sum(0 <= n < N, a(n)/b(n) * (p(0)...p(n))/(q(0)...q(n)))
	// with appropriate N, and
	//   a(n) = 1, b(n) = 1, p(n) = p for n>0, q(n) = n*2^lq for n>0.
	var uintC actuallen = len+1; // 1 Schutz-Digit
	// How many terms to we need for M bits of precision? N terms suffice,
	// provided that
	//   1/(2^(N*lp)*N!) < 2^-M
	// <==   N*(log(N)-1)+N*lp*log(2) > M*log(2)
	// First approximation:
	//   N0 = M will suffice, so put N<=N0.
	// Second approximation:
	//   N1 = floor(M*log(2)/(log(N0)-1+lp*log(2))), slightly too small,
	//   so put N>=N1.
	// Third approximation:
	//   N2 = ceiling(M*log(2)/(log(N1)-1+lp*log(2))), slightly too large.
	//   N = N2+2, two more terms for safety.
	var uintL N0 = intDsize*actuallen;
	var uintL N1 = (uintL)(0.693147*intDsize*actuallen/(log((double)N0)-1.0+0.693148*lp));
	var uintL N2 = (uintL)(0.693148*intDsize*actuallen/(log((double)N1)-1.0+0.693147*lp))+1;
	var uintL N = N2+2;
	CL_ALLOCA_STACK;
	var cl_I* pv = (cl_I*) cl_alloca(N*sizeof(cl_I));
	var cl_I* qv = (cl_I*) cl_alloca(N*sizeof(cl_I));
	var uintL* qsv = (uintL*) cl_alloca(N*sizeof(uintL));
	var uintL n;
	init1(cl_I, pv[0]) (1);
	init1(cl_I, qv[0]) (1);
	for (n = 1; n < N; n++) {
		init1(cl_I, pv[n]) (p);
		init1(cl_I, qv[n]) ((cl_I)n << lq);
	}
	var cl_pq_series series;
	series.pv = pv; series.qv = qv; series.qsv = qsv;
	var cl_LF fsum = eval_rational_series(N,series,actuallen);
	for (n = 0; n < N; n++) {
		pv[n].~cl_I();
		qv[n].~cl_I();
	}
	return shorten(fsum,len); // verkürzen und fertig
}}
// Bit complexity (N = len, and if p has length O(log N) and ql = O(log N)):
// O(log(N)*M(N)).

