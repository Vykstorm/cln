// Timing tools.

#ifndef _CL_TIMING_H
#define _CL_TIMING_H

#include "cl_config.h"
#include "cl_intparam.h"
#include "cl_types.h"

#include "cl_io.h"

struct cl_timespec {
	uintL tv_sec;	// seconds since 1970-01-01
	sintL tv_nsec;	// nanoseconds, >= 0, < 1000000000
	// Constructors.
	cl_timespec () {}
	cl_timespec (uintL sec, sintL nsec)
		: tv_sec (sec), tv_nsec (nsec) {}
};

struct cl_time_duration {
	uintL tv_sec;	// seconds
	uintL tv_nsec;	// nanoseconds
	// Constructors.
	cl_time_duration () {}
	cl_time_duration (uintL sec)
		: tv_sec (sec), tv_nsec (0) {}
	cl_time_duration (uintL sec, uintL nsec)
		: tv_sec (sec), tv_nsec (nsec) {}
};

struct cl_time_consumption {
	cl_time_duration realtime;	// elapsed time
	cl_time_duration usertime;	// system's notion of user time/run time
};

extern const cl_time_duration operator- (const cl_timespec&, const cl_timespec&);
extern const cl_timespec operator+ (const cl_timespec&, const cl_time_duration&);
extern const cl_timespec operator- (const cl_timespec&, const cl_time_duration&);
extern const cl_time_duration operator+ (const cl_time_duration&, const cl_time_duration&);
extern const cl_time_duration operator- (const cl_time_duration&, const cl_time_duration&);

extern const cl_timespec cl_current_time ();
extern const cl_time_consumption cl_current_time_consumption ();

// Report a time consumption.
// (Should better be a virtual member function of `cl_time_consumption').
extern void cl_timing_report (cl_ostream, const cl_time_consumption&);

struct cl_timing {
	// Constructor, starts the time interval.
	cl_timing (cl_time_consumption& accumulator);
	cl_timing (cl_ostream destination = cl_stderr);
	cl_timing (const char *, cl_ostream destination = cl_stderr);
	// Destructor, closes the time interval and does a report.
	~cl_timing ();	
//private:
	cl_time_consumption tmp;
	void (*report_fn) (const cl_timing&);
	void* report_destination;
	const char * comment;
};

// Macro for timing.
// Usage:
//     { CL_TIMING; computation(); }
// or  { CL_TIMING(accumulator); computation(); }
// or  { CL_TIMING(cl_stdout); computation(); }
// The timing interval starts immediately and ends at the closing brace.
#define CL_TIMING  CL_TIMING1(__LINE__)
#define CL_TIMING1(line)  CL_TIMING2(line)
#define CL_TIMING2(line)  cl_timing cl_timing_dummy_##line

#endif /* _CL_TIMING_H */
