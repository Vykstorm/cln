// constructor cl_timing(cl_ostream).

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_timing.h"


// Implementation.

static void report_stream (const cl_timing& t)
{
	var const cl_time_consumption usage_end = cl_current_time_consumption();
	var const cl_time_consumption& usage_start = t.tmp;
	var cl_time_consumption usage;
	usage.realtime = usage_end.realtime - usage_start.realtime;
	usage.usertime = usage_end.usertime - usage_start.usertime;

	var cl_ostream destination =
#if defined(CL_IO_STDIO)
		(FILE*) t.report_destination;
#endif
#if defined(CL_IO_IOSTREAM)
		*(ostream*) t.report_destination;
#endif
	if (t.comment)
		fprint(destination,t.comment);
	cl_timing_report(destination,usage);
	fprint(destination,"\n");
}

cl_timing::cl_timing (cl_ostream destination)
{
	report_fn = report_stream;
#if defined(CL_IO_STDIO)
	report_destination = destination;
#endif
#if defined(CL_IO_IOSTREAM)
	report_destination = &destination;
#endif
	comment = NULL;
	tmp = cl_current_time_consumption();
}

cl_timing::cl_timing (const char * msg, cl_ostream destination)
{
	report_fn = report_stream;
#if defined(CL_IO_STDIO)
	report_destination = destination;
#endif
#if defined(CL_IO_IOSTREAM)
	report_destination = &destination;
#endif
	comment = msg;
	tmp = cl_current_time_consumption();
}
