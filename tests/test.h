#include <cl_io.h>

#define ASSERT(expr)  \
  if (!(expr)) {					\
	fprint(cl_stderr,"Assertion failed! File ");	\
	fprint(cl_stderr,__FILE__);			\
	fprint(cl_stderr,", line ");			\
	fprintdecimal(cl_stderr,__LINE__);		\
	fprint(cl_stderr,".\n");			\
	error = 1;					\
  }

#define ASSERT1(expr,a)  \
  if (!(expr)) {					\
	fprint(cl_stderr,"Assertion failed! File ");	\
	fprint(cl_stderr,__FILE__);			\
	fprint(cl_stderr,", line ");			\
	fprintdecimal(cl_stderr,__LINE__);		\
	fprint(cl_stderr,".\n");			\
	fprint(cl_stderr,#a" = ");			\
	fprint(cl_stderr,a);				\
	fprint(cl_stderr,"\n");				\
	error = 1;					\
  }

#define ASSERT2(expr,a,b)  \
  if (!(expr)) {					\
	fprint(cl_stderr,"Assertion failed! File ");	\
	fprint(cl_stderr,__FILE__);			\
	fprint(cl_stderr,", line ");			\
	fprintdecimal(cl_stderr,__LINE__);		\
	fprint(cl_stderr,".\n");			\
	fprint(cl_stderr,#a" = ");			\
	fprint(cl_stderr,a);				\
	fprint(cl_stderr,"\n"#b" = ");			\
	fprint(cl_stderr,b);				\
	fprint(cl_stderr,"\n");				\
	error = 1;					\
  }

#define ASSERT3(expr,a,b,c)  \
  if (!(expr)) {					\
	fprint(cl_stderr,"Assertion failed! File ");	\
	fprint(cl_stderr,__FILE__);			\
	fprint(cl_stderr,", line ");			\
	fprintdecimal(cl_stderr,__LINE__);		\
	fprint(cl_stderr,".\n");			\
	fprint(cl_stderr,#a" = ");			\
	fprint(cl_stderr,a);				\
	fprint(cl_stderr,"\n"#b" = ");			\
	fprint(cl_stderr,b);				\
	fprint(cl_stderr,"\n"#c" = ");			\
	fprint(cl_stderr,c);				\
	fprint(cl_stderr,"\n");				\
	error = 1;					\
  }

#define ASSERT4(expr,a,b,c,d)  \
  if (!(expr)) {					\
	fprint(cl_stderr,"Assertion failed! File ");	\
	fprint(cl_stderr,__FILE__);			\
	fprint(cl_stderr,", line ");			\
	fprintdecimal(cl_stderr,__LINE__);		\
	fprint(cl_stderr,".\n");			\
	fprint(cl_stderr,#a" = ");			\
	fprint(cl_stderr,a);				\
	fprint(cl_stderr,"\n"#b" = ");			\
	fprint(cl_stderr,b);				\
	fprint(cl_stderr,"\n"#c" = ");			\
	fprint(cl_stderr,c);				\
	fprint(cl_stderr,"\n"#d" = ");			\
	fprint(cl_stderr,d);				\
	fprint(cl_stderr,"\n");				\
	error = 1;					\
  }

