dnl The CLN manual says that without CFLAGS or CXXFLAGS being set compilation
dnl will happen with -O.  However, AC_PROG_CC and AC_PROG_CXX set CFLAGS and
dnl CXXFLAGS to "-g -O2", which produces way too large binaries.


dnl Wrapper around AC_PROG_CC setting CFLAGS to plain "-O" as opposed to
dnl "-g -O2" for the GNU compiler (unless CFLAGS was set before).
AC_DEFUN([CL_PROG_CC],
[cl_test_CFLAGS=${CFLAGS+set}
# Make sure this macro does not come after AC_PROG_CC.
# Otherwise CFLAGS would already be set.
AC_BEFORE([$0],[AC_PROG_CC])dnl
AC_PROG_CC([$1])
if test "$cl_test_CFLAGS" != set && test "$ac_compiler_gnu" = yes; then
    CFLAGS="-O"
fi
])


dnl Wrapper around AC_PROG_CXX setting CXXFLAGS to plain "-O" as opposed to
dnl "-g -O2" for the GNU compiler (unless CXXFLAGS was set before).
AC_DEFUN([CL_PROG_CXX],
[cl_test_CXXFLAGS=${CXXFLAGS+set}
# Make sure this macro does not come after AC_PROG_CXX.
# Otherwise CXXFLAGS would already be set.
AC_BEFORE([$0],[AC_PROG_CXX])dnl
AC_PROG_CXX([$1])
if test "$cl_test_CXXFLAGS" != set && test "$ac_compiler_gnu" = yes; then
    CXXFLAGS="-O"
fi
])
