// IEEE floating-point

#ifndef _CL_IEEE_H
#define _CL_IEEE_H

// To make sure that cl_ieee.cc is linked in.
// NEED_IEEE_FLOATS()
#if (defined(linux) || defined(__linux)) // only needed on Linux
  #define NEED_IEEE_FLOATS()  \
    CL_REQUIRE(cl_ieee)							\
    static void* const CONCAT(cl_ieee_dummy_,__LINE__) = &cl_ieee_module;
#else
  #define NEED_IEEE_FLOATS()
#endif
extern int cl_ieee_module;

#endif /* _CL_IEEE_H */
