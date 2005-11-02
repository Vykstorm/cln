#include "test_I.h"
#include <cln/input.h>
#include <sstream>

int test_I_io (int iterations)
{
	int error = 0;
	for (int i = iterations; i > 0; i--) {
		cl_I a = testrandom_I();
		int base = iterations % (36-1) + 2;
		cl_read_flags rflags = {syntax_integer, lsyntax_standard, base};
		stringstream buf;
		print_integer(buf, base, a);
		ASSERT1(a == read_integer(buf, rflags), a);
	}
	return error;
}
