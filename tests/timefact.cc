#include <cln/number.h>
#include <cln/io.h>
#include <cln/integer.h>
#include <cln/random.h>
#include "cl_I.h"
#include <stdlib.h>
#include <string.h>
#include <cln/timing.h>

int main (int argc, char * argv[])
{
	int repetitions = 1;
	if ((argc >= 3) && !strcmp(argv[1],"-r")) {
		repetitions = atoi(argv[2]);
		argc -= 2; argv += 2;
	}
	if (argc < 2)
		exit(1);
	cl_I m = cl_I(argv[1]);
	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    cl_I f = factorial(FN_to_L(m));
	}
}
