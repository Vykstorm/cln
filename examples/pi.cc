// Compute decimal Archimedes' constant Pi to arbitrary accuracy.

#include <cln/output.h>
#include <cln/real.h>
#include <cln/real_io.h>
#include <cctype>
#include <cstdlib>
#include <cstring>

using namespace std;
using namespace cln;

static void
usage (ostream &os)
{
	os << "Usage: pi [digits]\n";
	os << "Compute decimal Archimedes' constant Pi to arbitrary accuracy.\n\n";
	os << "      --help                 display this help and exit\n";
	os << "      --version              output version information and exit\n";
	os << "      --bibliography         output recommended readings and exit\n";
}

int
main (int argc, char * argv[])
{
	int digits = 100;
	if (argc > 1) {
		if (argc == 2 && !strcmp(argv[1],"--help")) {
			usage(cout);
			return 0;
		}
		if (argc == 2 && !strcmp(argv[1],"--version")) {
			cout << "pi (cln) " << CL_VERSION_MAJOR << "." << CL_VERSION_MINOR << endl;
			cout << "Written by Bruno Haible." << endl;
			cout << endl;
			cout << "Copyright (C) 1998-2001 Bruno Haible." << endl;
			cout << "This is free software; see the source for copying conditions.  There is NO" << endl;
			cout << "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE." << endl;
			cout << endl;
			return 0;
		}
		if (argc == 2 && !strcmp(argv[1],"--bibliography")) {
			cout << "Recommended readings:\n";
			cout << "\"Pi\", by Joerg Arndt and Christoph Haenel (1999)\n";
			cout << "\"Pi: A Source Book\" by Lennart Berggren, Jonathan Borwein, Peter Borwein (1997)" << endl;
			return 0;
		}
		if (argc == 2 && isdigit(argv[1][0])) {
			digits = atoi(argv[1]);
		} else {
			usage(cerr);
			return 1;
		}
	}
	
	cl_F p = pi(float_format(digits));
	// make CLN believe this number has default_float_format to suppress
	// exponent marker which would be quite boring for 3.1416...
	cl_print_flags cpf;
	cpf.default_float_format = float_format(p);
	print_real(cout, cpf, p);
	cout << endl;
	
	return 0;
}
