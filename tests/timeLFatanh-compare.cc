#include <cl_number.h>
#include <cl_io.h>
#include <cl_float.h>
#include <cl_lfloat.h>
#include "cl_LF.h"
#include <cl_complex.h>
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
	if (argc < 3)
		exit(1);
	extern double cl_atanhx_factor;
	extern int cl_atanh_algo;
	uintL len = atoi(argv[1]);
	cl_atanhx_factor = atof(argv[2]);
#if 0
	cl_LF one = cl_I_to_LF(1,len);
	cl_F x = scale_float(random_F(one),-1);
	cout << x << endl;
#else
	cl_F x = sqrt(cl_I_to_LF(2,len))-1;
#endif
	cl_N y;
	ln(cl_I_to_LF(1000,len+10)); // fill cache
	cl_atanh_algo = 0;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { y = atanh(x); }
	}
	cout << y << endl;
	cl_atanh_algo = 1;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { y = atanh(x); }
	}
	cout << y << endl;
}
