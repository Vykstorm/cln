// Print the continued fraction of a real number.

// We work with real numbers and integers.
#include <cln/real.h>
#include <cln/integer.h>

// We do I/O.
#include <cln/io.h>
#include <cln/integer_io.h>

using namespace cln;

// Our private error handling: return to the main program.
#include <setjmp.h>
jmp_buf restartpoint;
namespace cln {
	void cl_abort (void) { longjmp(restartpoint,1); }
}

int main (int argc, char* argv[])
{
	for (int i = 1; i < argc; i++) {
		const char * arg = argv[i];
		if (setjmp(restartpoint))
			continue;
		// Convert argument to its internal representation:
		cl_R x = arg;
		// Check sign.
		if (minusp(x)) {
			stdout << '-';
			x = -x;
		}
		fprint(stdout, "[");
		const char* separator = "; ";
		for (;;) {
			// Split x into integral and fractional part.
			cl_R_div_t x_split = floor2(x);
			stdout << x_split.quotient;
			x = x_split.remainder;
			if (zerop(x))
				break;
			stdout << separator;
			separator = ", ";
			// Invert x.
			x = recip(x);
		}
		stdout << ']' << std::endl;
	}
}
