#include <cl_io.h>

extern int test_nt_jacobi (int iterations);

#define RUN(tester,iterations)  \
	fprint(cl_stdout,"Testing "#tester"...\n"); \
	error |= tester (iterations);

int test_nt (int iterations)
{
	int error = 0;
	RUN(test_nt_jacobi,iterations);
	return error;
}
