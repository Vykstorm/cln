//#define WANT_OBFUSCATING_OPERATORS
#include <cl_number.h>
#include <cl_io.h>
//#include <cl_complex.h>
//#include <cl_real.h>
//#include <cl_real_io.h>
//#include <cl_output.h>
//#include <cl_ffloat.h>
#include <cl_integer.h>
#include <cl_integer_io.h>
//#include <cl_modinteger.h>
//#include <cl_numtheory.h>
#include <cl_timing.h>

#define DUMP(expr)  \
	fprint(cl_stdout, #expr" = "); fprint(cl_stdout, expr); fprint(cl_stdout, "\n");

int main (int argc, char* argv[])
{
	(void)argc; (void)argv;

#if 0
	cl_F pi = cl_pi((cl_float_format_t)10000);
	fprint(cl_stdout, pi);
	fprint(cl_stdout, "\n");
#endif

#if 0
	cl_FF a;
	cl_FF x1 = "-0.2173f0";
	cl_FF x2 = "5.5084f9";
	cl_FF y = "-1.19698f9";
	fprint(cl_stdout, "x1 = "); print_float_binary(cl_stdout,x1); fprint(cl_stdout, " = "); fprint(cl_stdout,x1); fprint(cl_stdout, "\n");
	fprint(cl_stdout, "x2 = "); print_float_binary(cl_stdout,x2); fprint(cl_stdout, " = "); fprint(cl_stdout,x2); fprint(cl_stdout, "\n");
	fprint(cl_stdout, "y = "); print_float_binary(cl_stdout,y); fprint(cl_stdout, " = "); fprint(cl_stdout,y); fprint(cl_stdout, "\n");
	cl_FF x = x1*x2;
	fprint(cl_stdout, "x1*x2 = "); print_float_binary(cl_stdout,x); fprint(cl_stdout, " = "); fprint(cl_stdout,x); fprint(cl_stdout, "\n");
#endif

#if 0
	cl_I x = 10;
	cl_I y = ++x;
	x *= 2;
	x++;
	fprint(cl_stdout, "x = "); fprint(cl_stdout, x); fprint(cl_stdout, "\n");
	fprint(cl_stdout, "y = "); fprint(cl_stdout, y); fprint(cl_stdout, "\n");
#endif

#if 0
	cl_I a = "77371252437321868671713407";
	cl_I w;
	cl_boolean squarep = isqrt(a,&w);
	DUMP(squarep);
	DUMP(w);
	DUMP(expt_pos(w,2) <= a);
	DUMP(a < expt_pos(w+1,2));
#endif

#if 0
	cl_I m = "79228162513111556826425457664";
	cl_I a = "19787815858762768436681494528";
	cl_modint_ring R = cl_find_modint_ring(m);
	cl_I b = R->retract(R->canonhom(a));
	cl_I c = mod(a,abs(m));
	DUMP(b);
	DUMP(c);
	DUMP(b==c);
#endif

#if 0
	cl_N x = argv[1];
	cl_N y = sinh(x);
	{ CL_TIMING; y = sinh(x); }
	cout << y << endl;
#endif

#if 0
	cl_I x = argv[1];
	cout << x << " is " << (isprobprime(x) ? "" : "not ") << "prime" << endl;
#endif

#if 0
	cl_float_format_t f = cl_float_format(atoi(argv[1]));
	extern cl_LF cl_zeta3 (uintC len);
	uintC len = (uintL)f/intDsize+1;
	{ CL_TIMING; cout << cl_zeta(2,f) << endl; }
	{ CL_TIMING; cout << expt(cl_pi(f),2)/6 << endl; }
	{ CL_TIMING; cout << cl_zeta(3,f) << endl; }
	{ CL_TIMING; cout << cl_zeta3(len) << endl; }
	{ CL_TIMING; cout << cl_zeta(4,f) << endl; }
#endif

	cl_I a = cl_I(argv[1]);
	cl_I b = cl_I(argv[2]);
	cl_I u;
	cl_I v;
	cl_I g = xgcd(a,b,&u,&v);
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "gcd = " << gcd(a,b) << endl;
	cout << "g = " << g << endl;
	cout << "u = " << u << endl;
	cout << "v = " << v << endl;

#if 0
	cl_F x = argv[1];
	cout << x << endl;
#endif

}
