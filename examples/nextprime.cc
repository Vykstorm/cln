// This program prints the smallest probable prime >= x, x being given on the
// command line.

// We work with real numbers and integers.
#include <cl_real.h>
#include <cl_integer.h>

// We do I/O.
#include <cl_io.h>
#include <cl_integer_io.h>

// The function nextprobprime() is part of the number theory package.
#include <cl_numtheory.h>

int main (int argc, char* argv[])
{
	if (argc != 2) {
		fprint(cl_stderr, "Usage: nextprime x\n");
		exit(1);
	}
	cl_R x = (cl_R)argv[1];
	cl_I p = nextprobprime(x);
	fprint(cl_stdout, p);
	fprint(cl_stdout, "\n");
}
