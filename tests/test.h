#include <cln/io.h>
using namespace std;
using namespace cln;

#define ASSERT(expr)  \
  if (!(expr)) {					\
	stderr << "Assertion failed! File " << __FILE__ << ", line " << __LINE__ << endl;	\
	error = 1;					\
  }

#define ASSERT1(expr,a)  \
  if (!(expr)) {					\
	stderr << "Assertion failed! File " << __FILE__ << ", line " << __LINE__ << endl;	\
	stderr << #a" = " << a << endl;			\
	error = 1;					\
  }

#define ASSERT2(expr,a,b)  \
  if (!(expr)) {					\
	stderr << "Assertion failed! File " << __FILE__ << ", line " << __LINE__ << endl;	\
	stderr << #a" = " << a << endl;			\
	stderr << #b" = " << b << endl;			\
	error = 1;					\
  }

#define ASSERT3(expr,a,b,c)  \
  if (!(expr)) {					\
	stderr << "Assertion failed! File " << __FILE__ << ", line " << __LINE__ << endl;	\
	stderr << #a" = " << a << endl;			\
	stderr << #b" = " << b << endl;			\
	stderr << #c" = " << c << endl;			\
	error = 1;					\
  }

#define ASSERT4(expr,a,b,c,d)  \
  if (!(expr)) {					\
	stderr << "Assertion failed! File " << __FILE__ << ", line " << __LINE__ << endl;	\
	stderr << #a" = " << a << endl;			\
	stderr << #b" = " << b << endl;			\
	stderr << #c" = " << c << endl;			\
	stderr << #d" = " << d << endl;			\
	error = 1;					\
  }
