// Compute and print the n-th Fibonacci number.

// We work with integers and real numbers.
#include <cl_integer.h>
#include <cl_real.h>

// We do I/O.
#include <cl_io.h>
#include <cl_integer_io.h>

// We use the timing functions.
#include <cl_timing.h>

// Declare the exit() function.
#include <stdlib.h>

// F_n is defined through the recurrence relation
//      F_0 = 0, F_1 = 1, F_(n+2) = F_(n+1) + F_n.
// The following addition formula holds:
//      F_(n+m)   = F_(m-1) * F_n + F_m * F_(n+1)  for m >= 1, n >= 0.
// (Proof: For fixed m, the LHS and the RHS satisfy the same recurrence
// w.r.t. n, and the initial values (n=0, n=1) agree. Hence all values agree.)
// Replace m by m+1:
//      F_(n+m+1) = F_m * F_n + F_(m+1) * F_(n+1)      for m >= 0, n >= 0
// Now put in m = n, to get
//      F_(2n) = (F_(n+1)-F_n) * F_n + F_n * F_(n+1) = F_n * (2*F_(n+1) - F_n)
//      F_(2n+1) = F_n ^ 2 + F_(n+1) ^ 2
// hence
//      F_(2n+2) = F_(n+1) * (2*F_n + F_(n+1))

struct twofibs {
	cl_I u; // F_n
	cl_I v; // F_(n+1)
	// Constructor.
	twofibs (const cl_I& uu, const cl_I& vv) : u (uu), v (vv) {}
};

// Returns F_n and F_(n+1). Assume n>=0.
static const twofibs fibonacci2 (int n)
{
	if (n==0)
		return twofibs(0,1);
	int m = n/2; // floor(n/2)
	twofibs Fm = fibonacci2(m);
	// Since a squaring is cheaper than a multiplication, better use
	// three squarings instead of one multiplication and two squarings.
	cl_I u2 = square(Fm.u);
	cl_I v2 = square(Fm.v);
	if (n==2*m) {
		// n = 2*m
		cl_I uv2 = square(Fm.v - Fm.u);
		return twofibs(v2 - uv2, u2 + v2);
	} else {
		// n = 2*m+1
		cl_I uv2 = square(Fm.u + Fm.v);
		return twofibs(u2 + v2, uv2 - u2);
	}
}

// Returns just F_n. Assume n>=0.
const cl_I fibonacci (int n)
{
	if (n==0)
		return 0;
	int m = n/2; // floor(n/2)
	twofibs Fm = fibonacci2(m);
	if (n==2*m) {
		// n = 2*m
		// Here we don't use the squaring formula because
		// one multiplication is cheaper than two squarings.
		cl_I& u = Fm.u;
		cl_I& v = Fm.v;
		return u * ((v << 1) - u);
	} else {
		// n = 2*m+1
		cl_I u2 = square(Fm.u);
		cl_I v2 = square(Fm.v);
		return u2 + v2;
	}
}

// Returns just F_n, computed as the nearest integer to
// ((1+sqrt(5))/2)^n/sqrt(5). Assume n>=0.
const cl_I fibonacci_slow (int n)
{
	// Need a precision of ((1+sqrt(5))/2)^-n.
	cl_float_format_t prec = cl_float_format((int)(0.208987641*n+5));
	cl_R sqrt5 = sqrt(cl_float(5,prec));
	cl_R phi = (1+sqrt5)/2;
	return round1( expt(phi,n)/sqrt5 );
}

#ifndef TIMING

int main (int argc, char* argv[])
{
	if (argc != 2) {
		fprint(cl_stderr, "Usage: fibonacci n\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	fprint(cl_stdout, "fib(");
	fprintdecimal(cl_stdout, n);
	fprint(cl_stdout, ") = ");
	fprint(cl_stdout, fibonacci(n));
	fprint(cl_stdout, "\n");
}

#else // TIMING

int main (int argc, char* argv[])
{
	int repetitions = 1;
	if ((argc >= 3) && !strcmp(argv[1],"-r")) {
		repetitions = atoi(argv[2]);
		argc -= 2; argv += 2;
	}
	if (argc != 2) {
		fprint(cl_stderr, "Usage: fibonacci n\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	{ CL_TIMING;
		fprint(cl_stdout, "fib(");
		fprintdecimal(cl_stdout, n);
		fprint(cl_stdout, ") = ");
		for (int rep = repetitions-1; rep > 0; rep--)
			fibonacci(n);
		fprint(cl_stdout, fibonacci(n));
		fprint(cl_stdout, "\n");
	}
	{ CL_TIMING;
		fprint(cl_stdout, "fib(");
		fprintdecimal(cl_stdout, n);
		fprint(cl_stdout, ") = ");
		for (int rep = repetitions-1; rep > 0; rep--)
			fibonacci_slow(n);
		fprint(cl_stdout, fibonacci_slow(n));
		fprint(cl_stdout, "\n");
	}
}

#endif
