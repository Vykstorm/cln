#include <cl_number.h>
#include <cl_io.h>
#include <cl_float.h>
#include <cl_float_io.h>
#include <cl_real.h>
#include <cl_random.h>
#include <stdlib.h>
#include <string.h>
#include <cl_timing.h>

int main (int argc, char * argv[])
{
	int repetitions = 1;
	if ((argc >= 3) && !strcmp(argv[1],"-r")) {
		repetitions = atoi(argv[2]);
		argc -= 2; argv += 2;
	}
	if (argc < 2)
		exit(1);
#if 0
	uintL len = atoi(argv[1]);
	extern cl_LF compute_pi_brent_salamin (uintC len);
	extern cl_LF compute_pi_brent_salamin_quartic (uintC len);
	extern cl_LF compute_pi_ramanujan_163 (uintC len);
	extern cl_LF compute_pi_ramanujan_163_fast (uintC len);
	cl_LF p;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { p = compute_pi_brent_salamin(len); }
	}
//	cout << p << endl;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { p = compute_pi_brent_salamin_quartic(len); }
	}
//	cout << p << endl;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { p = compute_pi_ramanujan_163(len); }
	}
//	cout << p << endl;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { p = compute_pi_ramanujan_163_fast(len); }
	}
//	cout << p << endl;
#else
	// Here the argument is N *decimal* digits, not N*32 bits!
	int n = atoi(argv[1]);
	cl_float_format_t prec = cl_float_format(n);
	cl_F p;
	fprint(cl_stderr, "Computing pi\n");
	{ CL_TIMING; p = cl_pi(prec); }
	fprint(cl_stderr, "Converting pi to decimal\n");
	{ CL_TIMING; cout << p << endl << endl; }
#endif
}
