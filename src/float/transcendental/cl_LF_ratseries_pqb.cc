// eval_rational_series().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_LF_tran.h"


// Implementation.

#include "cl_lfloat.h"
#include "cl_integer.h"
#include "cl_abort.h"
#include "cl_LF.h"

// Subroutine.
// Evaluates S = sum(N1 <= n < N2, a(n)/b(n) * (p(N1)...p(n))/(q(N1)...q(n)))
// and returns P = p(N1)...p(N2-1), Q = q(N1)...q(N2-1), B = B(N1)...B(N2-1)
// and T = B*Q*S (all integers). On entry N1 < N2.
// P will not be computed if a NULL pointer is passed.

static void eval_pqb_series_aux (uintL N1, uintL N2,
                                 const cl_pqb_series& args,
                                 cl_I* P, cl_I* Q, cl_I* B, cl_I* T)
{
	switch (N2 - N1) {
	case 0:
		cl_abort(); break;
	case 1:
		if (P) { *P = args.pv[N1]; }
		*Q = args.qv[N1];
		*B = args.bv[N1];
		*T = args.pv[N1];
		break;
	case 2: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		if (P) { *P = p01; }
		*Q = args.qv[N1] * args.qv[N1+1];
		*B = args.bv[N1] * args.bv[N1+1];
		*T = args.bv[N1+1] * args.qv[N1+1] * args.pv[N1]
		   + args.bv[N1] * p01;
		break;
		}
	case 3: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		var cl_I p012 = p01 * args.pv[N1+2];
		if (P) { *P = p012; }
		var cl_I q12 = args.qv[N1+1] * args.qv[N1+2];
		*Q = args.qv[N1] * q12;
		var cl_I b12 = args.bv[N1+1] * args.bv[N1+2];
		*B = args.bv[N1] * b12;
		*T = b12 * q12 * args.pv[N1]
		   + args.bv[N1] * (args.bv[N1+2] * args.qv[N1+2] * p01
		                    + args.bv[N1+1] * p012);
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
		var cl_I b01 = args.bv[N1] * args.bv[N1+1];
		var cl_I b23 = args.bv[N1+2] * args.bv[N1+3];
		*B = b01 * b23;
		*T = b23 * (args.bv[N1+1] * q123 * args.pv[N1]
		            + args.bv[N1] * q23 * p01)
		   + b01 * (args.bv[N1+3] * args.qv[N1+3] * p012
		            + args.bv[N1+2] * p0123);
		break;
		}
	default: {
		var uintL Nm = (N1+N2)/2; // midpoint
		// Compute left part.
		var cl_I LP, LQ, LB, LT;
		eval_pqb_series_aux(N1,Nm,args,&LP,&LQ,&LB,&LT);
		// Compute right part.
		var cl_I RP, RQ, RB, RT;
		eval_pqb_series_aux(Nm,N2,args,(P?&RP:(cl_I*)0),&RQ,&RB,&RT);
		// Put together partial results.
		if (P) { *P = LP*RP; }
		*Q = LQ*RQ;
		*B = LB*RB;
		// S = LS + LP/LQ * RS, so T = RB*RQ*LT + LB*LP*RT.
		*T = RB*RQ*LT + LB*LP*RT;
		break;
		}
	}
}

static void eval_pqsb_series_aux (uintL N1, uintL N2,
                                  const cl_pqb_series& args,
                                  cl_I* P, cl_I* Q, uintL* QS, cl_I* B, cl_I* T)
{
	switch (N2 - N1) {
	case 0:
		cl_abort(); break;
	case 1:
		if (P) { *P = args.pv[N1]; }
		*Q = args.qv[N1];
		*QS = args.qsv[N1];
		*B = args.bv[N1];
		*T = args.pv[N1];
		break;
	case 2: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		if (P) { *P = p01; }
		*Q = args.qv[N1] * args.qv[N1+1];
		*QS = args.qsv[N1] + args.qsv[N1+1];
		*B = args.bv[N1] * args.bv[N1+1];
		*T = ((args.bv[N1+1] * args.qv[N1+1] * args.pv[N1]) << args.qsv[N1+1])
		   + args.bv[N1] * p01;
		break;
		}
	case 3: {
		var cl_I p01 = args.pv[N1] * args.pv[N1+1];
		var cl_I p012 = p01 * args.pv[N1+2];
		if (P) { *P = p012; }
		var cl_I q12 = args.qv[N1+1] * args.qv[N1+2];
		*Q = args.qv[N1] * q12;
		*QS = args.qsv[N1] + args.qsv[N1+1] + args.qsv[N1+2];
		var cl_I b12 = args.bv[N1+1] * args.bv[N1+2];
		*B = args.bv[N1] * b12;
		*T = ((b12 * q12 * args.pv[N1]) << (args.qsv[N1+1] + args.qsv[N1+2]))
		   + args.bv[N1] * (((args.bv[N1+2] * args.qv[N1+2] * p01) << args.qsv[N1+2])
		                    + args.bv[N1+1] * p012);
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
		var cl_I b01 = args.bv[N1] * args.bv[N1+1];
		var cl_I b23 = args.bv[N1+2] * args.bv[N1+3];
		*B = b01 * b23;
		*T = ((b23 * (((args.bv[N1+1] * q123 * args.pv[N1]) << args.qsv[N1+1])
		              + args.bv[N1] * q23 * p01)) << (args.qsv[N1+2] + args.qsv[N1+3]))
		   + b01 * (((args.bv[N1+3] * args.qv[N1+3] * p012) << args.qsv[N1+3])
		            + args.bv[N1+2] * p0123);
		break;
		}
	default: {
		var uintL Nm = (N1+N2)/2; // midpoint
		// Compute left part.
		var cl_I LP, LQ, LB, LT;
		var uintL LQS;
		eval_pqsb_series_aux(N1,Nm,args,&LP,&LQ,&LQS,&LB,&LT);
		// Compute right part.
		var cl_I RP, RQ, RB, RT;
		var uintL RQS;
		eval_pqsb_series_aux(Nm,N2,args,(P?&RP:(cl_I*)0),&RQ,&RQS,&RB,&RT);
		// Put together partial results.
		if (P) { *P = LP*RP; }
		*Q = LQ*RQ;
		*QS = LQS+RQS;
		*B = LB*RB;
		// S = LS + LP/LQ * RS, so T = RB*RQ*LT + LB*LP*RT.
		*T = ((RB*RQ*LT) << RQS) + LB*LP*RT;
		break;
		}
	}
}

const cl_LF eval_rational_series (uintL N, const cl_pqb_series& args, uintC len)
{
	if (N==0)
		return cl_I_to_LF(0,len);
	var cl_I Q, B, T;
	if (!args.qsv) {
		eval_pqb_series_aux(0,N,args,NULL,&Q,&B,&T);
		return cl_I_to_LF(T,len) / cl_I_to_LF(B*Q,len);
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
		eval_pqsb_series_aux(0,N,args,NULL,&Q,&QS,&B,&T);
		return cl_I_to_LF(T,len) / scale_float(cl_I_to_LF(B*Q,len),QS);
	}
}
// Bit complexity (if p(n), q(n), a(n), b(n) have length O(log(n))):
// O(log(N)^2*M(N)).
