// cl_current_time().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_timing.h"


// Implementation.

#include "cl_t_config.h"

#if defined(HAVE_GETTIMEOFDAY)
  #include <sys/time.h>
  #ifdef GETTIMEOFDAY_DOTS
    extern "C" int gettimeofday (struct timeval * tp, ...);
  #else
    extern "C" int gettimeofday (struct timeval * tp, GETTIMEOFDAY_TZP_T tzp);
  #endif
#elif defined(HAVE_FTIME)
  #include <sys/timeb.h>
  #ifdef _WIN32
    extern "C" void ftime (struct timeb * tp);
  #else
    extern "C" int ftime (struct timeb * tp);
  #endif
#else
  #include <time.h>
#endif
#ifdef HAVE_PERROR_DECL
  #include <errno.h>
  #include <stdio.h>
#else
  extern "C" int perror (const char *);
#endif

const cl_timespec cl_current_time ()
{
#if defined(HAVE_GETTIMEOFDAY)
	var struct timeval tv;
	if (gettimeofday(&tv,NULL) != 0) {
		perror("gettimeofday");
		tv.tv_sec = 0; tv.tv_usec = 0;
	}
	return cl_timespec(tv.tv_sec,
			   tv.tv_usec * (1000000000/1000000)
			  );
#elif defined(HAVE_FTIME)
	var struct timeb timebuf;
	ftime(&timebuf);
	return cl_timespec(timebuf.time,
			   (uintL)timebuf.millitm * (1000000000/1000)
			  );
#else
	return cl_timespec(time(NULL),0);
#endif
}
