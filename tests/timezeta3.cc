#include <cl_number.h>
#include <cl_io.h>
#include <cl_float.h>
#include <cl_real.h>
#include <stdlib.h>
#include <string.h>
#include <cl_timing.h>
#include "cl_LF.h"

int main (int argc, char * argv[])
{
	int repetitions = 1;
	if ((argc >= 3) && !strcmp(argv[1],"-r")) {
		repetitions = atoi(argv[2]);
		argc -= 2; argv += 2;
	}
	if (argc < 2)
		exit(1);
	uintL len = atoi(argv[1]);
	extern cl_LF cl_zeta (int s, uintC len);
	extern cl_LF compute_zeta_exp (int s, uintC len);
	extern cl_LF compute_zeta_cvz1 (int s, uintC len);
	extern cl_LF compute_zeta_cvz2 (int s, uintC len);
	extern cl_LF cl_zeta3 (uintC len);
	cl_LF p;
	ln(cl_I_to_LF(1000,len+10)); // fill cache
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { p = compute_zeta_exp(3,len); }
	}
	cout << p << endl;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { p = compute_zeta_cvz1(3,len); }
	}
	cout << p << endl;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { p = compute_zeta_cvz2(3,len); }
	}
	cout << p << endl;
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { p = cl_zeta3(len); }
	}
	cout << p << endl;
}
