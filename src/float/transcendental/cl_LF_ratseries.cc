// eval_rational_series().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_LF_tran.h"


// Implementation.

namespace cln {

// Subroutine.
// Evaluates S = sum(N1 <= n < N2, a(n)/b(n) * (p(N1)...p(n))/(q(N1)...q(n)))
// and returns P = p(N1)...p(N2-1), Q = q(N1)...q(N2-1), B = B(N1)...B(N2-1)
// and T = B*Q*S (all integers). On entry N1 < N2.
// P will not be computed if a NULL pointer is passed.

const cl_LF eval_rational_series (uintL N, const cl_rational_series& args, uintC len)
{
	if (args.pv)
		if (args.qv)
			if (args.bv)
				if (args.av) {
					var cl_pqab_series series =
					  { args.pv, args.qv, args.av, args.bv, args.qsv };
					return eval_rational_series(N,series,len);
				} else {
					var cl_pqb_series series =
					  { args.pv, args.qv, args.bv, args.qsv };
					return eval_rational_series(N,series,len);
				}
			else
				if (args.av) {
					var cl_pqa_series series =
					  { args.pv, args.qv, args.av, args.qsv };
					return eval_rational_series(N,series,len);
				} else {
					var cl_pq_series series =
					  { args.pv, args.qv, args.qsv };
					return eval_rational_series(N,series,len);
				}
		else
			if (args.bv)
				if (args.av) {
					var cl_pab_series series =
					  { args.pv, args.av, args.bv };
					return eval_rational_series(N,series,len);
				} else {
					var cl_pb_series series =
					  { args.pv, args.bv };
					return eval_rational_series(N,series,len);
				}
			else
				if (args.av) {
					var cl_pa_series series =
					  { args.pv, args.av };
					return eval_rational_series(N,series,len);
				} else {
					var cl_p_series series =
					  { args.pv };
					return eval_rational_series(N,series,len);
				}
	else
		if (args.qv)
			if (args.bv)
				if (args.av) {
					var cl_qab_series series =
					  { args.qv, args.av, args.bv, args.qsv };
					return eval_rational_series(N,series,len);
				} else {
					var cl_qb_series series =
					  { args.qv, args.bv, args.qsv };
					return eval_rational_series(N,series,len);
				}
			else
				if (args.av) {
					var cl_qa_series series =
					  { args.qv, args.av, args.qsv };
					return eval_rational_series(N,series,len);
				} else {
					var cl_q_series series =
					  { args.qv, args.qsv };
					return eval_rational_series(N,series,len);
				}
		else
			if (args.bv)
				if (args.av) {
					var cl_ab_series series =
					  { args.av, args.bv };
					return eval_rational_series(N,series,len);
				} else {
					var cl_b_series series =
					  { args.bv };
					return eval_rational_series(N,series,len);
				}
			else
				if (args.av) {
					var cl_a_series series =
					  { args.av };
					return eval_rational_series(N,series,len);
				} else {
					var cl__series series =
					  { };
					return eval_rational_series(N,series,len);
				}
}
// Bit complexity (if p(n), q(n), a(n), b(n) have length O(log(n))):
// O(log(N)^2*M(N)).

}  // namespace cln
