#include <cl_number.h>
#include <cl_io.h>
#include <cl_integer.h>
#include <stdlib.h>
#include <string.h>
#include <cl_timing.h>

int main (int argc, char * argv[])
{
	int limit = 1000;
	int repetitions = 1;
	while (argc >= 3) {
		if (!strcmp(argv[1],"-r")) {
			repetitions = atoi(argv[2]);
			argc -= 2; argv += 2;
			continue;
		}
		if (!strcmp(argv[1],"-l")) {
			limit = atoi(argv[2]);
			argc -= 2; argv += 2;
			continue;
		}
		break;
	}
	if (argc < 1)
		exit(1);

	fprint(cl_stderr, "Limit: ");
	fprintdecimal(cl_stderr, limit);
	fprint(cl_stderr, "\n");
	fprint(cl_stderr, "Number of repetitions: ");
	fprintdecimal(cl_stderr, repetitions);
	fprint(cl_stderr, "\n");

	{ CL_TIMING;
	  for (int rep = repetitions; rep > 0; rep--)
	    { cl_I u = 1, v = 1, p = 1, q = 1;
	      for (int k = 1; k <= limit; k++)
	        { cl_I w = u+v;
	          u = v; v = w;
	          p = p*w; q = lcm(q,w);
	        }
	    }
	}

}
