// eval_rational_series().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_LF_tran.h"


// Implementation.

#include "cln/lfloat.h"
#include "cln/integer.h"
#include "cln/abort.h"
#include "cl_LF.h"

namespace cln {

// Subroutine.
// Evaluates S = sum(N1 <= n < N2, a(n)/b(n) * (p(N1)...p(n))/(q(N1)...q(n)))
// and returns P = p(N1)...p(N2-1), Q = q(N1)...q(N2-1), B = B(N1)...B(N2-1)
// and T = B*Q*S (all integers). On entry N1 < N2.
// P will not be computed if a NULL pointer is passed.

static void eval_pq_series_aux (uintL N1, uintL N2,
                                const cl_pq_series& args,
                                cl_I* P, cl_I* Q, cl_I* T)
{
	switch (N2 - N1) {
	case 0:
		cl_abort(); break;
	case 1:
		if (P) { *P = args.pv[N1]; }
		*Q = args.qv[N1];
		*T = args.pv[N1];
		break;
	case 2: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		if (P) { *P = p01; }
		*Q = args.qv[N1] * args.qv[N1+1];
		*T = args.qv[N1+1] * args.pv[N1]
		   + p01;
		break;
		}
	case 3: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		var cl_I p012 = p01 * args.pv[N1+2];
		if (P) { *P = p012; }
		var cl_I q12 = args.qv[N1+1] * args.qv[N1+2];
		*Q = args.qv[N1] * q12;
		*T = q12 * args.pv[N1]
		   + args.qv[N1+2] * p01
		   + p012;
		break;
		}
	case 4: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		var cl_I p012 = p01 * args.pv[N1+2];
		var cl_I p0123 = p012 * args.pv[N1+3];
		if (P) { *P = p0123; }
		var cl_I q23 = args.qv[N1+2] * args.qv[N1+3];
		var cl_I q123 = args.qv[N1+1] * q23;
		*Q = args.qv[N1] * q123;
		*T = q123 * args.pv[N1]
		   + q23 * p01
		   + args.qv[N1+3] * p012
		   + p0123;
		break;
		}
	default: {
		var uintL Nm = (N1+N2)/2; // midpoint
		// Compute left part.
		var cl_I LP, LQ, LT;
		eval_pq_series_aux(N1,Nm,args,&LP,&LQ,&LT);
		// Compute right part.
		var cl_I RP, RQ, RT;
		eval_pq_series_aux(Nm,N2,args,(P?&RP:(cl_I*)0),&RQ,&RT);
		// Put together partial results.
		if (P) { *P = LP*RP; }
		*Q = LQ*RQ;
		// S = LS + LP/LQ * RS, so T = RQ*LT + LP*RT.
		*T = RQ*LT + LP*RT;
		break;
		}
	}
}

static void eval_pqs_series_aux (uintL N1, uintL N2,
                                 const cl_pq_series& args,
                                 cl_I* P, cl_I* Q, uintL* QS, cl_I* T)
{
	switch (N2 - N1) {
	case 0:
		cl_abort(); break;
	case 1:
		if (P) { *P = args.pv[N1]; }
		*Q = args.qv[N1];
		*QS = args.qsv[N1];
		*T = args.pv[N1];
		break;
	case 2: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		if (P) { *P = p01; }
		*Q = args.qv[N1] * args.qv[N1+1];
		*QS = args.qsv[N1] + args.qsv[N1+1];
		*T = ((args.qv[N1+1] * args.pv[N1]) << args.qsv[N1+1])
		   + p01;
		break;
		}
	case 3: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		var cl_I p012 = p01 * args.pv[N1+2];
		if (P) { *P = p012; }
		var cl_I q12 = args.qv[N1+1] * args.qv[N1+2];
		*Q = args.qv[N1] * q12;
		*QS = args.qsv[N1] + args.qsv[N1+1] + args.qsv[N1+2];
		*T = ((q12 * args.pv[N1]) << (args.qsv[N1+1] + args.qsv[N1+2]))
		   + ((args.qv[N1+2] * p01) << args.qsv[N1+2])
		   + p012;
		break;
		}
	case 4: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		var cl_I p012 = p01 * args.pv[N1+2];
		var cl_I p0123 = p012 * args.pv[N1+3];
		if (P) { *P = p0123; }
		var cl_I q23 = args.qv[N1+2] * args.qv[N1+3];
		var cl_I q123 = args.qv[N1+1] * q23;
		*Q = args.qv[N1] * q123;
		*QS = args.qsv[N1] + args.qsv[N1+1] + args.qsv[N1+2] + args.qsv[N1+3];
		*T = ((((((q123 * args.pv[N1]) << args.qsv[N1+1])
		         + q23 * p01) << args.qsv[N1+2])
		       + args.qv[N1+3] * p012) << args.qsv[N1+3])
		   + p0123;
		break;
		}
	default: {
		var uintL Nm = (N1+N2)/2; // midpoint
		// Compute left part.
		var cl_I LP, LQ, LT;
		var uintL LQS;
		eval_pqs_series_aux(N1,Nm,args,&LP,&LQ,&LQS,&LT);
		// Compute right part.
		var cl_I RP, RQ, RT;
		var uintL RQS;
		eval_pqs_series_aux(Nm,N2,args,(P?&RP:(cl_I*)0),&RQ,&RQS,&RT);
		// Put together partial results.
		if (P) { *P = LP*RP; }
		*Q = LQ*RQ;
		*QS = LQS+RQS;
		// S = LS + LP/LQ * RS, so T = RQ*LT + LP*RT.
		*T = ((RQ*LT) << RQS) + LP*RT;
		break;
		}
	}
}

const cl_LF eval_rational_series (uintL N, const cl_pq_series& args, uintC len)
{
	if (N==0)
		return cl_I_to_LF(0,len);
	var cl_I Q, T;
	if (!args.qsv) {
		eval_pq_series_aux(0,N,args,NULL,&Q,&T);
		return cl_I_to_LF(T,len) / cl_I_to_LF(Q,len);
	} else {
		// Precomputation of the shift counts:
		// Split qv[n] into qv[n]*2^qsv[n].
		{
			var cl_I* qp = args.qv;
			var uintL* qsp = args.qsv;
			for (var uintL n = 0; n < N; n++, qp++, qsp++) {
				// Pull out maximal power of 2 out of *qp = args.qv[n].
				var uintL qs = 0;
				if (!zerop(*qp)) {
					qs = ord2(*qp);
					if (qs > 0)
						*qp = *qp >> qs;
				}
				*qsp = qs;
			}
		}
		// Main computation.
		var uintL QS;
		eval_pqs_series_aux(0,N,args,NULL,&Q,&QS,&T);
		return cl_I_to_LF(T,len) / scale_float(cl_I_to_LF(Q,len),QS);
	}
}
// Bit complexity (if p(n), q(n), a(n), b(n) have length O(log(n))):
// O(log(N)^2*M(N)).

}  // namespace cln
