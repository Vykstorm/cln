#include <cl_number.h>
#include <cl_io.h>
#include <cl_integer.h>
#include <cl_lfloat.h>
#include <cl_rational.h>
#include <cl_float_io.h>
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
	if (argc < 4)
		exit(1);
	uintL m1 = atoi(argv[1]);
	cl_I m2 = cl_I(argv[2]);
	cl_I M2 = (cl_I)1 << (intDsize*m2);
	cl_I m3 = cl_I(argv[3]);
	cl_I M3 = (cl_I)1 << (intDsize*m3);
	cl_float_format_t M1 = (cl_float_format_t)(m1*intDsize);
	cl_I u;
	cl_I v;
	do { u = random_I(M2); } while (zerop(u));
	do { v = random_I(M3); } while (zerop(v) || gcd(u,v) > 1);
	cl_RA y = u / v;
	cl_F p;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { p = cl_float(u,M1)/cl_float(v,M1); }
	}
	cout << p << endl;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { p = cl_float(y,M1); }
	}
	cout << p << endl;
}
