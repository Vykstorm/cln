#include <cl_number.h>
#include <cl_io.h>
#include <cl_integer.h>
#include <cl_integer_io.h>
#include <cl_float.h>
#include <cl_real.h>
#include <stdlib.h>
#include <string.h>
#include <cl_timing.h>

int main (int argc, char * argv[])
{
	int digits = 100;
	int repetitions = 1;
	while (argc >= 3) {
		if (!strcmp(argv[1],"-r")) {
			repetitions = atoi(argv[2]);
			argc -= 2; argv += 2;
			continue;
		}
		if (!strcmp(argv[1],"-n")) {
			digits = atoi(argv[2]);
			argc -= 2; argv += 2;
			continue;
		}
		break;
	}
	if (argc < 1)
		exit(1);

	fprint(cl_stderr, "Number of digits: ");
	fprintdecimal(cl_stderr, digits);
	fprint(cl_stderr, "\n");
	fprint(cl_stderr, "Number of repetitions: ");
	fprintdecimal(cl_stderr, repetitions);
	fprint(cl_stderr, "\n");

	cl_float_format_t prec = cl_float_format(digits);
	cl_float_format_t prec2 = cl_float_format(digits*2);
	cl_I pow = expt_pos(10,digits);
	cl_I x1 = floor1((sqrt(cl_float(5,prec2))+1)/2 * expt_pos(pow,2));
	cl_I x2 = floor1(sqrt(cl_float(3,prec)) * pow);
	cl_I x3 = pow+1;

	fprint(cl_stderr, "multiplication\n");
	{ cl_I r = x1*x2;
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = x1*x2; }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "division\n");
	{ cl_I_div_t qr = floor2(x1,x2);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { qr = floor2(x1,x2); }
	  }
	  cout << qr.quotient << endl << qr.remainder << endl << endl;
	}

	fprint(cl_stderr, "isqrt\n");
	{ cl_I r = isqrt(x3);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = isqrt(x3); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "gcd\n");
	{ cl_I r = gcd(x1,x2);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = gcd(x1,x2); }
	  }
	  cout << r << endl << endl;
	}

}
