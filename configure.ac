dnl  AUTOCONF configuration for CLN
dnl
dnl  configure.ac ---<autoconf>--->> configure
dnl
dnl  configure    ---<sh>--->> config.status
dnl                      --->> include/cln/config.h
dnl        cln-config.in --->> cln-config
dnl          Makefile.in --->> Makefile
dnl      src/Makefile.in --->> src/Makefile
dnl
dnl  Makefile   ---<make>--->> libcln.a
dnl
dnl
AC_INIT(src/integer/gcd/cl_I_gcd.cc)
AC_CONFIG_AUX_DIR(autoconf)
AC_CONFIG_HEADER(include/cln/config.h include/cln/version.h src/base/cl_base_config.h src/base/cl_gmpconfig.h src/float/cl_float_config.h src/timing/cl_t_config.h)
AC_PROG_MAKE_SET
dnl This piece of sed script replaces every line containing '@subdir@'
dnl by several consecutive lines, each referencing one subdir.
extrasub="$extrasub"'
/@subdir@/{
h
g
s/@subdir@/src/
p
g
s/@subdir@/tests/
p
g
s/@subdir@/benchmarks/
p
g
s/@subdir@/examples/
p
g
s/@subdir@/doc/
p
d
}
'
dnl
dnl           checks for programs
dnl
AC_PROG_CC
                      dnl sets variable CC
AC_PROG_CPP
                      dnl sets variable CPP
AC_PROG_CXX
                      dnl sets variable CXX
AC_PROG_CXXCPP
                      dnl sets variable CXXCPP
CL_AS_UNDERSCORE
                      dnl sets variable AS_UNDERSCORE, DEFS ASM_UNDERSCORE
CL_PROG_RANLIB
                      dnl sets variable RANLIB
CL_PROG_INSTALL
                      dnl sets variables INSTALL, INSTALL_DATA, INSTALL_PROGRAM
dnl
dnl           check for host type
dnl
CL_CANONICAL_HOST(autoconf)
                      dnl sets variables host, host_cpu, host_vendor, host_os
CL_CANONICAL_HOST_CPU
                      dnl DEFS __${host_cpu}__
dnl
dnl           check for build configuration
dnl
                      dnl libcln depends on libm
PACKAGE=cln
                      dnl libtool wants PACKAGE
AC_PROG_LIBTOOL
                      dnl sets variable LIBTOOL

dnl Libtool's library version information for CLN.
dnl (Not to be confused with CLN's release version.)
dnl Making new releases:
dnl * increment CL_REVISION,
dnl * if any functions/classes have been added, removed or changed, increment
dnl   CL_CURRENT and set CL_REVISION to 0,
dnl * if any functions/classes have been added, increment CL_AGE,
dnl * if backwards compatibility has been broken, set CL_AGE to 0.
CL_CURRENT=2
CL_REVISION=4
CL_AGE=0
dnl make substitutions
AC_SUBST(CL_CURRENT)
AC_SUBST(CL_REVISION)
AC_SUBST(CL_AGE)
dnl release version
CL_VERSION_MAJOR=1
CL_VERSION_MINOR=1
CL_VERSION_PATCHLEVEL=5
dnl release version for cln/config.h, so it can be tested by the preprocessor
AC_DEFINE_UNQUOTED(CL_VERSION_MAJOR, $CL_VERSION_MAJOR)
AC_DEFINE_UNQUOTED(CL_VERSION_MINOR, $CL_VERSION_MINOR)
AC_DEFINE_UNQUOTED(CL_VERSION_PATCHLEVEL, $CL_VERSION_PATCHLEVEL)
dnl concatenated release version
CL_VERSION=$CL_VERSION_MAJOR.$CL_VERSION_MINOR.$CL_VERSION_PATCHLEVEL
AC_DEFINE_UNQUOTED(CL_VERSION, $CL_VERSION)
AC_SUBST(CL_VERSION)

dnl
dnl           checks for compiler characteristics
dnl
AC_LANG_CPLUSPLUS
dnl
CL_BOOL
                      dnl DEFS HAVE_BOOL, bool
CL_LONGLONG
                      dnl DEFS HAVE_LONGLONG
CL_LONGDOUBLE
                      dnl DEFS HAVE_LONGDOUBLE
CL_TEMPLATE_NULL
                      dnl DEFS HAVE_TEMPLATE_NULL
CL_GLOBAL_CONSTRUCTORS
                      dnl DEFS CL_GLOBAL_CONSTRUCTOR_PREFIX, CL_GLOBAL_DESTRUCTOR_PREFIX
dnl
dnl           checks for header files
dnl
CL_UNISTD_H
                      dnl DEFS HAVE_UNISTD_H if exist unistd.h
dnl
dnl           checks for typedefs
dnl
dnl
dnl           checks for functions and declarations
dnl
CL_ALLOCA
                      dnl set variable ALLOCA, DEFS NO_ALLOCA
CL_FPU_CONTROL
                      dnl DEFS HAVE_FPU_CONTROL_T, HAVE_SETFPUCW
CL_GETTIMEOFDAY
                      dnl DEFS HAVE_GETTIMEOFDAY, GETTIMEOFDAY_DOTS, GETTIMEOFDAY_TZP_T
CL_FTIME
                      dnl DEFS HAVE_FTIME
CL_TIMES_CLOCK
                      dnl DEFS HAVE_TIMES_CLOCK
CL_RUSAGE
                      dnl DEFS HAVE_SYS_RESOURCE_H, HAVE_GETRUSAGE, HAVE_SYS_TIMES_H
CL_PERROR
                      dnl DEFS HAVE_PERROR_DECL
dnl
dnl           checks for compiler characteristics
dnl
CL_CHAR_UNSIGNED
                      dnl DEFS __CHAR_UNSIGNED__ if char is unsigned
test -d 'include/cln' || mkdir -p 'include/cln'
CL_MACHINE([integer types and behaviour],${srcdir}/autoconf/intparam.c,include/cln/intparam.h,cl_cv_file_intparam_h)
                      dnl builds include/cln/intparam.h
CL_MACHINE([floating-point types and behaviour],${srcdir}/autoconf/floatparam.c,include/cln/floatparam.h,cl_cv_file_floatparam_h)
                      dnl builds include/cln/floatparam.h
dnl
dnl           interfacing to GNU gmp (must be at least version 3)
dnl
AC_ARG_WITH(gmp, [  --with-gmp              use external fast low-level functions from GNU MP 3.
                          [default=yes]], ,with_gmp="yes")
if test "$with_gmp" = yes; then
  CL_GMP_H_VERSION
  if test "$cl_cv_new_gmp_h" = no; then with_gmp="no"; fi
  if test "$with_gmp" = yes; then
    CL_GMP_CHECK
    if test "$cl_cv_new_libgmp" = no; then with_gmp="no"; fi
  fi
fi
if test "$with_gmp" = yes; then
  CL_GMP_SET_UINTD
  AC_DEFINE(CL_USE_GMP)
else
  AC_MSG_WARN([disabling external GNU MP library])
fi
dnl
dnl           That's it.
dnl
for f in 'tests/.gdbinit'; do
  if test '!' -f "$f"; then
    echo "creating $f"
changequote(,)dnl
    g=`echo "$f" | sed -e 's,/[^/]*$,,'`
changequote([,])dnl
    test "$g" = "$f" || test -d "$g" || mkdir "$g"
    cp "$srcdir/$f" "$f"
  fi
done
AC_OUTPUT([Makefile src/Makefile tests/Makefile benchmarks/Makefile examples/Makefile doc/Makefile cln-config cln-config.1 cln.spec cln.pc], [chmod +x cln-config])
