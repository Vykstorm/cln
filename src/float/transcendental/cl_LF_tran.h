// cl_LF internals, transcendental functions

#ifndef _CL_LF_TRAN_H
#define _CL_LF_TRAN_H

#include "cln/integer.h"
#include "cln/lfloat.h"

namespace cln {

// Subroutine for evaluating
// sum(0 <= n < N, a(n)/b(n) * (p(0)...p(n))/(q(0)...q(n)))
// where all the entries are small integers (ideally polynomials in n).
// This is fast because it groups factors together before multiplying.
// Arguments:
//   Vectors p[0..N-1], q[0..N-1], a[0..N-1], b[0..N-1], N.
//   Some of the vectors (a,b,p,q) can be a NULL pointer, all of its entries
//   are then understood to be 1.
//   If given, a vector qs[0..N-1] which the evaluation routine may use to
//   split off q[n] into q[n]*2^qs[n]. qs may be NULL, in that case no shift
//   optimizations will be used. (They are worth it only if a significant
//   amount of multiplication work can be saved by shifts.)
// Result will be a cl_LF with len digits.

struct cl_rational_series {
	// To be set explicitly.
	const cl_I* pv;
	      cl_I* qv;
	const cl_I* av;
	const cl_I* bv;
	     uintC* qsv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_rational_series& args, uintC len);

// In each the special cases below, none of (a,b,p,q) can be NULL. But qs can
// still be given or NULL.

struct cl_pqab_series {
	const cl_I* pv;
	      cl_I* qv;
	const cl_I* av;
	const cl_I* bv;
	     uintC* qsv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_pqab_series& args, uintC len);

struct cl_pqb_series {
	const cl_I* pv;
	      cl_I* qv;
	const cl_I* bv;
	     uintC* qsv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_pqb_series& args, uintC len);

struct cl_pqa_series {
	const cl_I* pv;
	      cl_I* qv;
	const cl_I* av;
	     uintC* qsv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_pqa_series& args, uintC len);

struct cl_pq_series {
	const cl_I* pv;
	      cl_I* qv;
	     uintC* qsv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_pq_series& args, uintC len);

struct cl_pab_series {
	const cl_I* pv;
	const cl_I* av;
	const cl_I* bv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_pab_series& args, uintC len);

struct cl_pb_series {
	const cl_I* pv;
	const cl_I* bv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_pb_series& args, uintC len);

struct cl_pa_series {
	const cl_I* pv;
	const cl_I* av;
};
extern const cl_LF eval_rational_series (uintC N, const cl_pa_series& args, uintC len);

struct cl_p_series {
	const cl_I* pv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_p_series& args, uintC len);

struct cl_qab_series {
	      cl_I* qv;
	const cl_I* av;
	const cl_I* bv;
	     uintC* qsv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_qab_series& args, uintC len);

struct cl_qb_series {
	      cl_I* qv;
	const cl_I* bv;
	     uintC* qsv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_qb_series& args, uintC len);

struct cl_qa_series {
	      cl_I* qv;
	const cl_I* av;
	     uintC* qsv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_qa_series& args, uintC len);

struct cl_q_series {
	      cl_I* qv;
	     uintC* qsv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_q_series& args, uintC len);

struct cl_ab_series {
	const cl_I* av;
	const cl_I* bv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_ab_series& args, uintC len);

struct cl_b_series {
	const cl_I* bv;
};
extern const cl_LF eval_rational_series (uintC N, const cl_b_series& args, uintC len);

struct cl_a_series {
	const cl_I* av;
};
extern const cl_LF eval_rational_series (uintC N, const cl_a_series& args, uintC len);

struct cl__series {
};
extern const cl_LF eval_rational_series (uintC N, const cl__series& args, uintC len);


// In this alternate implementation the series is not represented as a couple
// of arrays, but as a method returning each tuple (p(n),q(n),a(n),b(n))
// in turn. This is preferrable if the a(n) are big, in order to avoid too
// much memory usage at the same time.
// Some of the factors (a,b) may be omitted. They are then understood to be 1.
// The next function is called N times and is expected to return
// (p(n),q(n),a(n),b(n)) for n=0..N-1 in that order.

struct cl_pqab_series_term {
	cl_I p;
	cl_I q;
	cl_I a;
	cl_I b;
};
struct cl_pqab_series_stream {
	cl_pqab_series_term (*nextfn)(cl_pqab_series_stream&);
	cl_pqab_series_term next () { return nextfn(*this); }
	// Constructor.
	cl_pqab_series_stream (cl_pqab_series_term (*n)(cl_pqab_series_stream&)) : nextfn (n) {}
};
extern const cl_LF eval_rational_series (uintC N, cl_pqab_series_stream& args, uintC len);

struct cl_pqb_series_term {
	cl_I p;
	cl_I q;
	cl_I b;
};
struct cl_pqb_series_stream {
	cl_pqb_series_term (*nextfn)(cl_pqb_series_stream&);
	cl_pqb_series_term next () { return nextfn(*this); }
	// Constructor.
	cl_pqb_series_stream (cl_pqb_series_term (*n)(cl_pqb_series_stream&)) : nextfn (n) {}
};
extern const cl_LF eval_rational_series (uintC N, cl_pqb_series_stream& args, uintC len);

struct cl_pqa_series_term {
	cl_I p;
	cl_I q;
	cl_I a;
};
struct cl_pqa_series_stream {
	cl_pqa_series_term (*nextfn)(cl_pqa_series_stream&);
	cl_pqa_series_term next () { return nextfn(*this); }
	// Constructor.
	cl_pqa_series_stream (cl_pqa_series_term (*n)(cl_pqa_series_stream&)) : nextfn (n) {}
};
extern const cl_LF eval_rational_series (uintC N, cl_pqa_series_stream& args, uintC len);

struct cl_pq_series_term {
	cl_I p;
	cl_I q;
};
struct cl_pq_series_stream {
	cl_pq_series_term (*nextfn)(cl_pq_series_stream&);
	cl_pq_series_term next () { return nextfn(*this); }
	// Constructor.
	cl_pq_series_stream (cl_pq_series_term (*n)(cl_pq_series_stream&)) : nextfn (n) {}
};
extern const cl_LF eval_rational_series (uintC N, cl_pq_series_stream& args, uintC len);


// [Generalization.]
// Subroutine:
// Evaluates S = sum(N1 <= n < N2, (p(N1)...p(n))/(q(N1)...q(n)))
// and U = sum(N1 <= n < N2,
//             (c(N1)/d(N1)+...+c(n)/d(n))*(p(N1)...p(n))/(q(N1)...q(n)))
// and returns
//     P = p(N1)...p(N2-1),
//     Q = q(N1)...q(N2-1),
//     T = Q*S,
//     C/D = c(N1)/d(N1)+...+c(N2-1)/d(N2-1),
//     V = D*Q*U,
// all integers. On entry N1 < N2.
struct cl_pqcd_series_term {
	cl_I p;
	cl_I q;
	cl_I c;
	cl_I d;
};
struct cl_pqcd_series_result {
	cl_I P;
	cl_I Q;
	cl_I T;
	cl_I C;
	cl_I D;
	cl_I V;
};
extern void eval_pqcd_series_aux (uintC N, cl_pqcd_series_term* args, cl_pqcd_series_result& Z, bool rightmost = true);
// Ditto, but returns U/S.
extern const cl_LF eval_pqcd_series (uintC N, cl_pqcd_series_term* args, uintC len);

// [Special case c(n)=1.]
// Subroutine:
// Evaluates S = sum(N1 <= n < N2, (p(N1)...p(n))/(q(N1)...q(n)))
// and U = sum(N1 <= n < N2, (1/d(N1)+...+1/d(n))*(p(N1)...p(n))/(q(N1)...q(n)))
// and returns
//     P = p(N1)...p(N2-1),
//     Q = q(N1)...q(N2-1),
//     T = Q*S,
//     C/D = 1/d(N1)+...+1/d(N2-1),
//     V = D*Q*U,
// all integers. On entry N1 < N2.
struct cl_pqd_series_term {
	cl_I p;
	cl_I q;
	cl_I d;
};
struct cl_pqd_series_result {
	cl_I P;
	cl_I Q;
	cl_I T;
	cl_I C;
	cl_I D;
	cl_I V;
};
extern void eval_pqd_series_aux (uintC N, cl_pqd_series_term* args, cl_pqd_series_result& Z, bool rightmost = true);
// Ditto, but returns U/S.
extern const cl_LF eval_pqd_series (uintC N, cl_pqd_series_term* args, uintC len);

}  // namespace cln

#endif /* _CL_LF_TRAN_H */
