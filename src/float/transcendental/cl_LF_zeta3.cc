// cl_zeta3().

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

const cl_LF cl_zeta3 (uintC len)
{
	// Method:
	//            /infinity                                  \ 
	//            | -----       (n + 1)       2              |
	//        1   |  \      (-1)        (205 n  - 160 n + 32)|
	//        -   |   )     ---------------------------------|
	//        2   |  /              5                 5      |
	//            | -----          n  binomial(2 n, n)       |
	//            \ n = 1                                    /
	//
	// The formula used to compute Zeta(3) has reference in the paper
	// "Acceleration of Hypergeometric Series via the WZ method" by
	// T. Amdeberhan and Doron Zeilberger, to appear in the Electronic
	// Journal of Combinatorics [Wilf Festschrift Volume].
	//
	// Computation of the sum:
	// Evaluate a sum(0 <= n < N, a(n)/b(n) * (p(0)...p(n))/(q(0)...q(n)))
	// with appropriate N, and
	//   a(n) = 205*n^2+250*n+77, b(n) = 1,
	//   p(0) = 1, p(n) = -n^5 for n>0, q(n) = 32*(2n+1)^5.
	var uintC actuallen = len+2; // 2 Schutz-Digits
	var uintL N = ceiling(actuallen*intDsize,10);
	// 1024^-N <= 2^(-intDsize*actuallen).
	CL_ALLOCA_STACK;
	var cl_I* av = (cl_I*) cl_alloca(N*sizeof(cl_I));
	var cl_I* pv = (cl_I*) cl_alloca(N*sizeof(cl_I));
	var cl_I* qv = (cl_I*) cl_alloca(N*sizeof(cl_I));
	var uintL n;
	for (n = 0; n < N; n++) {
		init1(cl_I, av[n]) (205*square((cl_I)n) + 250*(cl_I)n + 77);
		if (n==0)
			init1(cl_I, pv[n]) (1);
		else
			init1(cl_I, pv[n]) (-expt_pos(n,5));
		init1(cl_I, qv[n]) (expt_pos(2*n+1,5)<<5);
	}
	var cl_pqa_series series;
	series.av = av;
	series.pv = pv; series.qv = qv; series.qsv = NULL;
	var cl_LF sum = eval_rational_series(N,series,actuallen);
	for (n = 0; n < N; n++) {
		av[n].~cl_I();
		pv[n].~cl_I();
		qv[n].~cl_I();
	}
	return scale_float(shorten(sum,len),-1);
}
// Bit complexity (N := len): O(log(N)^2*M(N)).

// Timings of the above algorithm, on an i486 33 MHz, running Linux.
//    N   sum_exp sum_cvz1 sum_cvz2 hypgeom
//    10     1.17    0.081   0.125   0.013
//    25     5.1     0.23    0.50    0.045
//    50    15.7     0.66    1.62    0.14
//   100    45.5     1.93    5.4     0.44
//   250   169      13.1    25.1     2.03
//   500   436      56.5    70.6     6.44
//  1000           236     192      18.2
//  2500                            78.3
//  5000                           202
// 10000                           522
// 25000                          1512
// 50000                          3723
// asymp.    FAST     N^2    FAST    FAST
// (FAST means O(log(N)^2*M(N)))
