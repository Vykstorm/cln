#include <cl_number.h>
#include <cl_io.h>
#include <cl_integer.h>
#include <cl_float.h>
#include <cl_float_io.h>
#include <cl_real.h>
#include <cl_real_io.h>
#include <cl_complex.h>
#include <cl_complex_io.h>
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
	fprint(cl_stderr, "Number of repetitions (except for pi,euler,e): ");
	fprintdecimal(cl_stderr, repetitions);
	fprint(cl_stderr, "\n");

	cl_float_format_t prec = cl_float_format(digits);
	cl_F x1 = sqrt(cl_float(2,prec));
	cl_F x2 = sqrt(cl_float(3,prec));
	cl_F x3 = The(cl_F)(log(cl_float(2,prec)));

	fprint(cl_stderr, "multiplication\n");
	{ cl_F r = x1*x2;
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = x1*x2; }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "sqrt\n");
	{ cl_F r = sqrt(x3);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = sqrt(x3); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "pi\n");
	{ cl_F r;
	  { CL_TIMING; r = cl_pi(prec); }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "eulerconst\n");
	{ cl_F r;
	  { CL_TIMING; r = cl_eulerconst(prec); }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "e\n");
	{ cl_F r;
	  { CL_TIMING; r = cl_exp1(prec); }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "exp\n");
	{ cl_F r = exp(-x1);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = exp(-x1); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "log\n");
	{ cl_N r = log(x2);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = log(x2); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "sin\n");
	{ cl_R r = sin(5*x1);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = sin(5*x1); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "cos\n");
	{ cl_R r = cos(5*x1);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = cos(5*x1); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "asin\n");
	{ cl_N r = asin(x3);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = asin(x3); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "acos\n");
	{ cl_N r = acos(x3);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = acos(x3); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "atan\n");
	{ cl_F r = atan(x3);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = atan(x3); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "sinh\n");
	{ cl_F r = sinh(x2);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = sinh(x2); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "cosh\n");
	{ cl_F r = cosh(x2);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = cosh(x2); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "asinh\n");
	{ cl_N r = asinh(x3);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = asinh(x3); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "acosh\n");
	{ cl_N r = acosh(1+x3);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = acosh(1+x3); }
	  }
	  cout << r << endl << endl;
	}

	fprint(cl_stderr, "atanh\n");
	{ cl_N r = atanh(x3);
	  { CL_TIMING;
	    for (int rep = repetitions; rep > 0; rep--)
	      { r = atanh(x3); }
	  }
	  cout << r << endl << endl;
	}

}
