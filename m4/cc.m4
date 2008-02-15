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
dnl "-g -O2" for the GNU compiler (unless CXXFLAGS was set before).  Also
dnl emits a warning if G++ is used and optimization turned off.
AC_DEFUN([CL_PROG_CXX],
[cl_test_CXXFLAGS=${CXXFLAGS+set}
# Make sure this macro does not come after AC_PROG_CXX.
# Otherwise CXXFLAGS would already be set.
AC_BEFORE([$0],[AC_PROG_CXX])dnl
AC_PROG_CXX([$1])
if test "$ac_compiler_gnu" = yes; then
  if test "$cl_test_CXXFLAGS" != set; then
    # User has not set CXXFLAGS.
    CXXFLAGS="-O"
  else
    # Warn if optimization has been turned off with GCC.
    # Optimization is used for module ordering.
    case $CXXFLAGS in
      [ *\ -O | -O | -O\ * | *\ -O\ * | -O[!0]* | *\ -O[!0]*) ;; ]
      *) AC_MSG_WARN([Optimization turned off. I recommend you unset CXXFLAGS.]);;
    esac
  fi
fi
])


dnl Checks whether the stack can be marked nonexecutable by passing an option
dnl to the C-compiler when acting on .s files. Appends that option to ASFLAGS.
dnl This macro is adapted from one found in GLIBC-2.3.5.
AC_DEFUN([CL_AS_NOEXECSTACK],[
AC_REQUIRE([AC_PROG_CC])
AC_CACHE_CHECK([whether --noexecstack is desirable for .s files], cl_cv_as_noexecstack, [dnl
  cat > conftest.c <<EOF
void foo() {}
EOF
  if AC_TRY_COMMAND([${CC} $CFLAGS $CPPFLAGS
                     -S -o conftest.s conftest.c >/dev/null]) \
     && grep -q .note.GNU-stack conftest.s \
     && AC_TRY_COMMAND([${CC} $CFLAGS $CPPFLAGS -Wa,--noexecstack
                       -c -o conftest.o conftest.s >/dev/null])
  then
    cl_cv_as_noexecstack=yes
  else
    cl_cv_as_noexecstack=no
  fi
  rm -f conftest*])
  if test "$cl_cv_as_noexecstack" = yes; then
    ASMFLAGS="$ASMFLAGS -Wa,--noexecstack"
  fi
  AC_SUBST(ASMFLAGS)
])


dnl Checks whether the compiler supports __attribute__((flatten)).
AC_DEFUN([CL_ATTRIBUTE_FLATTEN],[
AC_REQUIRE([AC_PROG_CXX])
AC_CACHE_CHECK([whether the compiler supports __attribute__((flatten))], cl_cv_have_attr_flatten, [dnl
  cat > conftest.cc <<EOF
void f() __attribute__((flatten));
EOF
if AC_TRY_COMMAND(${CXX-g++} $CXXFLAGS -c conftest.cc >/dev/null 2>conftest.stderr)
then
  if grep -i "warning" conftest.stderr > /dev/null; then
    cl_cv_have_attr_flatten=no
  else
    cl_cv_have_attr_flatten=yes
  fi
else
  cl_cv_have_attr_flatten=no
fi
rm -f conftest*
])
if test $cl_cv_have_attr_flatten = yes; then
  AC_DEFINE(CL_HAVE_ATTRIBUTE_FLATTEN)
fi
])
