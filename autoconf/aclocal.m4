dnl local autoconf macros
dnl Bruno Haible 21.9.1997
dnl Marcus Daniels 10.4.1997
dnl
AC_PREREQ(2.12)dnl
dnl
dnl without AC_MSG_...:   with AC_MSG_... and caching:
dnl   AC_TRY_CPP          CL_CPP_CHECK
dnl   AC_TRY_COMPILE      CL_COMPILE_CHECK
dnl   AC_TRY_LINK         CL_LINK_CHECK
dnl   AC_TRY_RUN          CL_RUN_CHECK - would require cross-compiling support
dnl Usage:
dnl AC_TRY_CPP(INCLUDES,
dnl            ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND])
dnl CL_CPP_CHECK(ECHO-TEXT, CACHE-ID,
dnl              INCLUDES,
dnl              ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND])
dnl AC_TRY_xxx(INCLUDES, FUNCTION-BODY,
dnl            ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND])
dnl CL_xxx_CHECK(ECHO-TEXT, CACHE-ID,
dnl              INCLUDES, FUNCTION-BODY,
dnl              ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND])
dnl
define(CL_CPP_CHECK,
[AC_MSG_CHECKING(for $1)
AC_CACHE_VAL($2,[
AC_TRY_CPP([$3], $2=yes, $2=no)
])
AC_MSG_RESULT([$]$2)
if test [$]$2 = yes; then
  ifelse([$4], , :, [$4])
ifelse([$5], , , [else
  $5
])dnl
fi
])dnl
dnl
define(CL_COMPILE_CHECK,
[AC_MSG_CHECKING(for $1)
AC_CACHE_VAL($2,[
AC_TRY_COMPILE([$3],[$4], $2=yes, $2=no)
])
AC_MSG_RESULT([$]$2)
if test [$]$2 = yes; then
  ifelse([$5], , :, [$5])
ifelse([$6], , , [else
  $6
])dnl
fi
])dnl
dnl
define(CL_LINK_CHECK,
[AC_MSG_CHECKING(for $1)
AC_CACHE_VAL($2,[
AC_TRY_LINK([$3],[$4], $2=yes, $2=no)
])
AC_MSG_RESULT([$]$2)
if test [$]$2 = yes; then
  ifelse([$5], , :, [$5])
ifelse([$6], , , [else
  $6
])dnl
fi
])dnl
dnl
dnl CL_PROTO(IDENTIFIER, ACTION-IF-NOT-FOUND, FINAL-PROTOTYPE)
define(CL_PROTO,
[AC_MSG_CHECKING([for $1 declaration])
AC_CACHE_VAL(cl_cv_proto_[$1], [$2
cl_cv_proto_$1="$3"])
cl_cv_proto_$1=`echo "[$]cl_cv_proto_$1" | tr -s ' ' | sed -e 's/( /(/'`
AC_MSG_RESULTPROTO([$]cl_cv_proto_$1)
])dnl
dnl
dnl CL_PROTO_RET(INCLUDES, DECL, CACHE-ID, TYPE-IF-OK, TYPE-IF-FAILS)
define(CL_PROTO_RET,
[AC_TRY_COMPILE([$1]
AC_LANG_EXTERN[$2
], [], $3="$4", $3="$5")
])dnl
dnl
dnl CL_PROTO_TRY(INCLUDES, ANSI-DECL, TRAD-DECL, ACTION-IF-OK, ACTION-IF-FAILS)
define(CL_PROTO_TRY,
[AC_TRY_COMPILE([$1]
AC_LANG_EXTERN
[#if defined(__STDC__) || defined(__cplusplus)
$2
#else
$3
#endif
], [], [$4], [$5])
])dnl
dnl
dnl CL_PROTO_CONST(INCLUDES, ANSI-DECL, TRAD-DECL, CACHE-ID)
define(CL_PROTO_CONST,
[CL_PROTO_TRY([$1], [$2], [$3], $4="", $4="const")]
)dnl
dnl
dnl CL_SILENT(ACTION)
dnl performs ACTION, with AC_MSG_CHECKING and AC_MSG_RESULT being defined away.
define(CL_SILENT,
[pushdef([AC_MSG_CHECKING],[:])dnl
pushdef([AC_CHECKING],[:])dnl
pushdef([AC_MSG_RESULT],[:])dnl
pushdef([AC_MSG_RESULTPROTO],[:])dnl
$1[]dnl
popdef([AC_MSG_RESULTPROTO])dnl
popdef([AC_MSG_RESULT])dnl
popdef([AC_CHECKING])dnl
popdef([AC_MSG_CHECKING])dnl
])dnl
dnl
AC_DEFUN(CL_AS_UNDERSCORE,
[AC_BEFORE([$0], [CL_GLOBAL_CONSTRUCTORS])
AC_CACHE_CHECK(for underscore in external names, cl_cv_prog_as_underscore, [
cat > conftest.c <<EOF
int foo() { return 0; }
EOF
# look for the assembly language name in the .s file
AC_TRY_COMMAND(${CC-cc} -S conftest.c) >/dev/null 2>&1
if grep _foo conftest.s >/dev/null ; then
  cl_cv_prog_as_underscore=yes
else
  cl_cv_prog_as_underscore=no
fi
rm -f conftest*
])
if test $cl_cv_prog_as_underscore = yes; then
  AS_UNDERSCORE=true
  AC_DEFINE(ASM_UNDERSCORE)
else
  AS_UNDERSCORE=false
fi
AC_SUBST(AS_UNDERSCORE)dnl
])dnl
dnl
AC_DEFUN(CL_PROG_RANLIB, [AC_CHECK_PROG(RANLIB, ranlib, ranlib, true)])dnl
dnl
AC_DEFUN(CL_PROG_INSTALL,
[dnl This is mostly copied from AC_PROG_INSTALL.
# Find a good install program.  We prefer a C program (faster),
# so one script is as good as another.  But avoid the broken or
# incompatible versions:
# SysV /etc/install, /usr/sbin/install
# SunOS /usr/etc/install
# IRIX /sbin/install
# AIX /bin/install
# AFS /usr/afsws/bin/install, which mishandles nonexistent args
# SVR4 /usr/ucb/install, which tries to use the nonexistent group "staff"
# ./install, which can be erroneously created by make from ./install.sh.
AC_MSG_CHECKING(for a BSD compatible install)
if test -z "$INSTALL"; then
AC_CACHE_VAL(cl_cv_path_install,
[  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:"
  for ac_dir in $PATH; do
    # Account for people who put trailing slashes in PATH elements.
    case "$ac_dir/" in
    /|./|.//|/etc/*|/usr/sbin/*|/usr/etc/*|/sbin/*|/usr/afsws/bin/*|/usr/ucb/*) ;;
    *)
      # OSF1 and SCO ODT 3.0 have their own names for install.
      for ac_prog in ginstall installbsd scoinst install; do
        if test -f $ac_dir/$ac_prog; then
	  if test $ac_prog = install &&
            grep dspmsg $ac_dir/$ac_prog >/dev/null 2>&1; then
	    # AIX install.  It has an incompatible calling convention.
	    # OSF/1 installbsd also uses dspmsg, but is usable.
	    :
	  else
	    if test $ac_prog = installbsd &&
	      grep src/bos $ac_dir/$ac_prog >/dev/null 2>&1; then
	      # AIX installbsd doesn't work without option "-g".
	      :
	    else
	      cl_cv_path_install="$ac_dir/$ac_prog -c"
	      break 2
	    fi
	  fi
	fi
      done
      ;;
    esac
  done
  IFS="$ac_save_ifs"
  # As a last resort, use cp.
  test -z "$cl_cv_path_install" && cl_cv_path_install="cp"
])dnl
  INSTALL="$cl_cv_path_install"
fi
dnl We do special magic for INSTALL instead of AC_SUBST, to get
dnl relative paths right. 
AC_MSG_RESULT($INSTALL)
AC_SUBST(INSTALL)dnl
# Use test -z because SunOS4 sh mishandles braces in ${var-val}.
# It thinks the first close brace ends the variable substitution.
test -z "$INSTALL_PROGRAM" && INSTALL_PROGRAM='$(INSTALL)'
AC_SUBST(INSTALL_PROGRAM)dnl
if test -z "$INSTALL_DATA"; then
  case "$INSTALL" in
    cp | */cp ) INSTALL_DATA='$(INSTALL)' ;;
    * )         INSTALL_DATA='$(INSTALL) -m 644' ;;
  esac
fi
AC_SUBST(INSTALL_DATA)dnl
])dnl
dnl
AC_DEFUN(CL_CANONICAL_HOST,
[AC_REQUIRE([AC_PROG_CC]) dnl Actually: AC_REQUIRE([CL_CC_WORKS])
dnl Set ac_aux_dir before the cache check, because AM_PROG_LIBTOOL needs it.
ac_aux_dir=${srcdir}/$1
AC_CACHE_CHECK(host system type, cl_cv_host, [
dnl A substitute for AC_CONFIG_AUX_DIR_DEFAULT, so we don't need install.sh.
ac_config_guess=$ac_aux_dir/config.guess
ac_config_sub=$ac_aux_dir/config.sub
dnl Mostly copied from AC_CANONICAL_HOST.
# Make sure we can run config.sub.
if $ac_config_sub sun4 >/dev/null 2>&1; then :
else AC_MSG_ERROR(can not run $ac_config_sub)
fi
host_alias=$host
case "$host_alias" in
NONE)
  case $nonopt in
  NONE) dnl config.guess needs to compile things
        host_alias=`export CC; $ac_config_guess` ;;
  *)    host_alias=$nonopt ;;
  esac ;;
esac
# Don't fail just because the system is not listed in GNU's database.
if test -n "$host_alias"; then
  host=`$ac_config_sub $host_alias`
else
  host=unknown-unknown-unknown
fi
cl_cv_host="$host"
])
host="$cl_cv_host"
host_cpu=`echo $host | sed 's/^\([^-]*\)-\([^-]*\)-\(.*\)$/\1/'`
host_vendor=`echo $host | sed 's/^\([^-]*\)-\([^-]*\)-\(.*\)$/\2/'`
host_os=`echo $host | sed 's/^\([^-]*\)-\([^-]*\)-\(.*\)$/\3/'`
AC_SUBST(host)dnl
AC_SUBST(host_cpu)dnl
AC_SUBST(host_vendor)dnl
AC_SUBST(host_os)dnl
])dnl
dnl
AC_DEFUN(CL_CANONICAL_HOST_CPU,
[AC_REQUIRE([CL_CANONICAL_HOST])AC_REQUIRE([AC_PROG_CC])
case "$host_cpu" in
changequote(,)dnl
  i[4567]86 )
    host_cpu=i386
    ;;
  alphaev[4-7] | alphaev56 | alphapca5[67] )
    host_cpu=alpha
    ;;
  hppa1.0 | hppa1.1 | hppa2.0 )
    host_cpu=hppa
    ;;
  powerpc )
    host_cpu=rs6000
    ;;
  c1 | c2 | c32 | c34 | c38 | c4 )
    host_cpu=convex
    ;;
changequote([,])dnl
  mips )
    AC_CACHE_CHECK([for 64-bit MIPS], cl_cv_host_mips64, [
AC_EGREP_CPP(yes,
[#if defined(_MIPS_SZLONG)
#if (_MIPS_SZLONG == 64)
/* We should also check for (_MIPS_SZPTR == 64), but gcc keeps this at 32. */
  yes
#endif
#endif
], cl_cv_host_mips64=yes, cl_cv_host_mips64=no)
])
if test $cl_cv_host_mips64 = yes; then
  host_cpu=mips64
fi
    ;;
dnl UltraSPARCs running Linux have `uname -m` = "sparc64", but the C compiler
dnl still generates 32-bit code.
  sparc | sparc64 )
    AC_CACHE_CHECK([for 64-bit SPARC], cl_cv_host_sparc64, [
AC_EGREP_CPP(yes,
[#if defined(__sparcv9) || defined(__arch64__)
  yes
#endif
], cl_cv_host_sparc64=yes, cl_cv_host_sparc64=no)
])
if test $cl_cv_host_sparc64 = yes; then
  host_cpu=sparc64
else
  host_cpu=sparc
fi
    ;;
esac
dnl was AC_DEFINE_UNQUOTED(__${host_cpu}__) but KAI C++ 3.2d doesn't like this
cat >> confdefs.h <<EOF
#ifndef __${host_cpu}__
#define __${host_cpu}__ 1
#endif
EOF
])dnl
dnl
AC_DEFUN(CL_LONGLONG,
[AC_CACHE_CHECK(for long long type, cl_cv_c_longlong, [
AC_TRY_RUN([int main()
{
/* long longs don't work right with gcc-2.7.2 on m68k */
/* long longs don't work right with gcc-2.7.2 on rs6000: avcall/tests.c gets
   miscompiled. */
#ifdef __GNUC__
#if defined(__m68k__) || (defined(_IBMR2) || defined(__powerpc))
#if (__GNUC__ == 2)
#if (__GNUC_MINOR__ <= 7)
  exit(1);
#endif
#endif
#endif
#endif
  { long x = 944938507; long y = 737962842; long z = 162359677;
    exit(!(((long long) x)*((long long) y)>>32 == z));
  }
}],
cl_cv_c_longlong=yes, cl_cv_c_longlong=no,
dnl When cross-compiling, don't assume anything.
cl_cv_c_longlong="guessing no")
])
case "$cl_cv_c_longlong" in
  *yes) AC_DEFINE(HAVE_LONGLONG) ;;
  *no) ;;
esac
])dnl
dnl
AC_DEFUN(CL_LONGDOUBLE,
[AC_CACHE_CHECK(for long double type, cl_cv_c_longdouble, [
AC_TRY_RUN([int main()
{ long double x = 2.7182818284590452354L; x = x*x; exit (x==0.0L); }],
cl_cv_c_longdouble=yes, cl_cv_c_longdouble=no,
dnl When cross-compiling, don't assume anything.
cl_cv_c_longdouble="guessing no")
])
case "$cl_cv_c_longdouble" in
  *yes) AC_DEFINE(HAVE_LONGDOUBLE) ;;
  *no) ;;
esac
])dnl
dnl
AC_DEFUN(CL_TEMPLATE_NULL,
[CL_COMPILE_CHECK([working template<>], cl_cv_c_templatenull,
[template <class T> class c {}; template <> class c<int> { int x; };], ,
AC_DEFINE(HAVE_TEMPLATE_NULL))
])dnl
dnl
AC_DEFUN(CL_UNISTD_H,
[AC_CHECK_HEADERS(unistd.h)]
)dnl
dnl
AC_DEFUN(CL_ALLOCA,
[# The Ultrix 4.2 mips builtin alloca declared by alloca.h only works
# for constant arguments.  Useless!
CL_LINK_CHECK(working alloca.h, cl_cv_header_alloca_h,
[#include <alloca.h>], [char *p = (char *) alloca(2 * sizeof(int));],
AC_DEFINE(HAVE_ALLOCA_H))dnl
decl="#ifdef __GNUC__
#define alloca __builtin_alloca
#else
#ifdef _MSC_VER
#include <malloc.h>
#define alloca _alloca
#else
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#else
#ifdef _AIX
 #pragma alloca
#else
#ifndef alloca
char *alloca ();
#endif
#endif
#endif
#endif
#endif
"
CL_LINK_CHECK([alloca], cl_cv_func_alloca,
$decl, [char *p = (char *) alloca(1);],
 , [alloca_missing=1])dnl
if test -n "$alloca_missing"; then
  # The SVR3 libPW and SVR4 libucb both contain incompatible functions
  # that cause trouble.  Some versions do not even contain alloca or
  # contain a buggy version.  If you still want to use their alloca,
  # use ar to extract alloca.o from them instead of compiling alloca.c.
  ALLOCA=alloca.${ac_objext}
  AC_DEFINE(NO_ALLOCA)
fi
AC_SUBST(ALLOCA)dnl
])dnl
dnl
AC_DEFUN(CL_FPU_CONTROL,
[dnl Check for Linux with <fpu_control.h> and fpu_control_t or __setfpucw().
dnl glibc versions since October 1998 define fpu_control_t. Earlier versions
dnl define and declare __setfpucw(). Very early Linux libc versions have none,
dnl and __fpu_control is of type `unsigned short'.
CL_COMPILE_CHECK([fpu_control_t], cl_cv_type_fpu_control_t,
[#include <fpu_control.h>], [fpu_control_t x;],
AC_DEFINE(HAVE_FPU_CONTROL_T))
CL_COMPILE_CHECK([__setfpucw], cl_cv_func_setfpucw,
[#include <fpu_control.h>], [__setfpucw(_FPU_IEEE);],
AC_DEFINE(HAVE_SETFPUCW))
])dnl
dnl
AC_DEFUN(CL_PERROR,
[AC_MSG_CHECKING(for perror declaration)
AC_CACHE_VAL(cl_cv_proto_perror, [
AC_TRY_COMPILE([
/* Some systems declare perror() in <errno.h>, some in <stdio.h>, some don't
   declare it at all. */
#include <stdio.h>
#include <errno.h>
]AC_LANG_EXTERN[double perror ();], [],
cl_cv_proto_perror=no, cl_cv_proto_perror=yes)
])
AC_MSG_RESULT([$cl_cv_proto_perror])
if test $cl_cv_proto_perror = yes; then
AC_DEFINE(HAVE_PERROR_DECL)
fi
])dnl
dnl
AC_DEFUN(CL_RUSAGE,
[AC_CHECK_HEADERS(sys/resource.h sys/times.h)dnl
if test $ac_cv_header_sys_resource_h = yes; then
  dnl HAVE_SYS_RESOURCE_H defined
  CL_LINK_CHECK([getrusage], cl_cv_func_getrusage,
[#include <sys/types.h> /* NetBSD 1.0 needs this */
#include <sys/time.h>
#include <sys/resource.h>],
    [struct rusage x; int y = RUSAGE_SELF; getrusage(y,&x); x.ru_utime.tv_sec;],
    AC_DEFINE(HAVE_GETRUSAGE))dnl
  if test $cl_cv_func_getrusage = yes; then
    CL_PROTO([getrusage], [
    CL_PROTO_TRY([
#include <stdlib.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <sys/types.h> /* NetBSD 1.0 needs this */
#include <sys/time.h>
#include <sys/resource.h>
],
[int getrusage (int who, struct rusage * rusage);],
[int getrusage();],
[cl_cv_proto_getrusage_arg1="int"],
[cl_cv_proto_getrusage_arg1="enum __rusage_who"])
], [extern int getrusage ($cl_cv_proto_getrusage_arg1, struct rusage *);])
    AC_DEFINE_UNQUOTED(RUSAGE_WHO_T,$cl_cv_proto_getrusage_arg1)
  fi
fi
])dnl
dnl
AC_DEFUN(CL_GETTIMEOFDAY,
[AC_BEFORE([$0], [CL_TIMES_CLOCK])
AC_CHECK_FUNCS(gettimeofday)dnl
if test $ac_cv_func_gettimeofday = yes; then
dnl HAVE_GETTIMEOFDAY is defined
CL_PROTO([gettimeofday], [
CL_PROTO_TRY([
#include <sys/types.h>
#include <sys/time.h>
], [int gettimeofday (struct timeval * tp, struct timezone * tzp);],
[int gettimeofday();],
cl_cv_proto_gettimeofday_dots=no
cl_cv_proto_gettimeofday_arg2="struct timezone *",
CL_PROTO_TRY([
#include <sys/types.h>
#include <sys/time.h>
], [int gettimeofday (struct timeval * tp, void * tzp);],
[int gettimeofday();],
cl_cv_proto_gettimeofday_dots=no
cl_cv_proto_gettimeofday_arg2="void *",
cl_cv_proto_gettimeofday_dots=yes
cl_cv_proto_gettimeofday_arg2="..."))
], [extern int gettimeofday (struct timeval *, $cl_cv_proto_gettimeofday_arg2);])
if test $cl_cv_proto_gettimeofday_dots = yes; then
AC_DEFINE(GETTIMEOFDAY_DOTS)
else
AC_DEFINE_UNQUOTED(GETTIMEOFDAY_TZP_T,$cl_cv_proto_gettimeofday_arg2)
fi
fi
])dnl
dnl
AC_DEFUN(CL_FTIME,
[AC_BEFORE([$0], [CL_TIMES_CLOCK])
AC_CHECK_FUNCS(ftime)])dnl
dnl
AC_DEFUN(CL_TIMES_CLOCK,
[AC_REQUIRE([CL_GETTIMEOFDAY])dnl
AC_REQUIRE([CL_FTIME])dnl
if test $ac_cv_func_gettimeofday = no -a $ac_cv_func_ftime = no; then
AC_CHECK_FUNC(times, , no_times=1)dnl
if test -z "$no_times"; then
AC_CACHE_CHECK(for times return value, cl_cv_func_times_return, [
AC_TRY_RUN([
#include <sys/types.h>
#include <time.h> /* needed for CLK_TCK */
#ifndef CLK_TCK
#include <sys/time.h> /* needed for CLK_TCK on SYSV PTX */
#endif
#include <sys/times.h>
int main ()
{ struct tms buffer;
  clock_t result1;
  clock_t result2;
  int ticks;
  result1 = times(&buffer);
  if ((result1 == (clock_t)0) || (result1 == (clock_t)(-1))) exit(1);
  sleep(1);
  result2 = times(&buffer);
  if ((result2 == (clock_t)0) || (result2 == (clock_t)(-1))) exit(1);
  ticks = result2 - result1;
  exit(!((ticks >= CLK_TCK/2) && (ticks <= 3*CLK_TCK/2)));
}], cl_cv_func_times_return=yes, cl_cv_func_times_return=no,
dnl When cross-compiling, don't assume anything.
cl_cv_func_times_return="guessing no")
])
case "$cl_cv_func_times_return" in
  *yes) AC_DEFINE(HAVE_TIMES_CLOCK) ;;
  *no)  ;;
esac
fi
fi
])dnl
dnl
AC_DEFUN(CL_GLOBAL_CONSTRUCTORS,
[AC_REQUIRE([CL_AS_UNDERSCORE])dnl
if test -n "$GCC"; then
AC_CACHE_CHECK(for the global constructors function prefix,
cl_cv_cplusplus_ctorprefix, [
cat > conftest.cc << EOF
struct foo { foo (); };
foo foobar;
EOF
# look for the assembly language name in the .s file
AC_TRY_COMMAND(${CXX-g++} $CXXFLAGS -S conftest.cc) >/dev/null 2>&1
if grep '_GLOBAL_\$I\$foobar' conftest.s >/dev/null ; then
  cl_cv_cplusplus_ctorprefix='_GLOBAL_$I$'
else
  if grep '_GLOBAL_\.I\.foobar' conftest.s >/dev/null ; then
    cl_cv_cplusplus_ctorprefix='_GLOBAL_.I.'
  else
    if grep '_GLOBAL__I_foobar' conftest.s >/dev/null ; then
      cl_cv_cplusplus_ctorprefix='_GLOBAL__I_'
    else
      cl_cv_cplusplus_ctorprefix=unknown
    fi
  fi
fi
rm -f conftest*
])
if test "$cl_cv_cplusplus_ctorprefix" '!=' unknown; then
  ac_value='"'"$cl_cv_cplusplus_ctorprefix"'"'
  AC_DEFINE_UNQUOTED(CL_GLOBAL_CONSTRUCTOR_PREFIX,$ac_value)
  ac_value=`echo "$ac_value" | sed -e 's,I,D,'`
  AC_DEFINE_UNQUOTED(CL_GLOBAL_DESTRUCTOR_PREFIX,$ac_value)
dnl Check whether the global constructors/destructors functions are file-scope
dnl only by default. This is the case in egcs-1.1.2 or newer.
AC_CACHE_CHECK(whether the global constructors function need to be exported,
cl_cv_cplusplus_ctorexport, [
cat > conftest1.cc << EOF
struct foo { foo (); };
foo foobar;
EOF
cat > conftest2.cc << EOF
#include "confdefs.h"
#ifdef ASM_UNDERSCORE
#define ASM_UNDERSCORE_PREFIX "_"
#else
#define ASM_UNDERSCORE_PREFIX ""
#endif
struct foo { foo (); };
foo::foo () {}
extern "C" void ctor (void) __asm__ (ASM_UNDERSCORE_PREFIX CL_GLOBAL_CONSTRUCTOR_PREFIX "foobar");
int main() { ctor(); return 0; }
EOF
if AC_TRY_COMMAND(${CXX-g++} -o conftest${ac_exeext} $CXXFLAGS $CPPFLAGS $LDFLAGS conftest1.cc conftest2.cc $LIBS 1>&5) >/dev/null 2>&1 && test -s conftest${ac_exeext}; then
  cl_cv_cplusplus_ctorexport=no
else
  cl_cv_cplusplus_ctorexport=yes
fi
rm -f conftest*
])
if test "$cl_cv_cplusplus_ctorexport" = yes; then
  AC_DEFINE(CL_NEED_GLOBALIZE_CTORDTOR)
fi
fi
fi
])dnl
dnl
AC_DEFUN(CL_CHAR_UNSIGNED,
[dnl This is mostly copied from AC_C_CHAR_UNSIGNED.
AC_CACHE_CHECK(whether characters are unsigned, ac_cv_c_char_unsigned, [
if test $ac_cv_prog_gcc = yes; then
  # GCC predefines this symbol on systems where it applies.
AC_EGREP_CPP(yes,
[#ifdef __CHAR_UNSIGNED__
  yes
#endif
], ac_cv_c_char_unsigned=yes, ac_cv_c_char_unsigned=no)
else
AC_TRY_RUN(
[/* volatile prevents gcc2 from optimizing the test away on sparcs.  */
#if !defined(__STDC__) || __STDC__ != 1
#define volatile
#endif
int main() {
  volatile char c = 255; exit(c < 0);
}], ac_cv_c_char_unsigned=yes, ac_cv_c_char_unsigned=no,
ac_cv_c_char_unsigned="guessing no")
fi])
if test $ac_cv_prog_gcc = no; then
  # GCC defines __CHAR_UNSIGNED__ by itself, no need to fix up.
  case "$ac_cv_c_char_unsigned" in
    *yes) AC_DEFINE(__CHAR_UNSIGNED__) ;;
    *no) ;;
  esac
fi
])dnl
dnl
AC_DEFUN(CL_BOOL,
[AC_LANG_SAVE()
AC_LANG_CPLUSPLUS()
CL_COMPILE_CHECK([bool type], cl_cv_cplusplus_bool, , [bool x;],
AC_DEFINE(HAVE_BOOL), AC_DEFINE(bool,int))dnl
AC_LANG_RESTORE()
])dnl
dnl
AC_DEFUN(CL_MACHINE,
[AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([CL_CHAR_UNSIGNED])dnl
cl_machine_file_c=$2
cl_machine_file_h=$3
if test $cross_compiling = no; then
if test -z "$[$4]"; then
AC_CHECKING(for [$1])
cat > conftest.$ac_ext <<EOF
#include "confdefs.h"
EOF
cat "$cl_machine_file_c" >> conftest.$ac_ext
ORIGCC="$CC"
if test $ac_cv_prog_gcc = yes; then
# gcc -O (gcc version <= 2.3.2) crashes when compiling long long shifts for
# target 80386. Strip "-O".
CC=`echo "$CC " | sed -e 's/-O //g'`
fi
AC_TRY_EVAL(ac_link)
CC="$ORIGCC"
if test -s conftest; then
  echo "creating $cl_machine_file_h"
  ./conftest > conftest.h
  if cmp -s "$cl_machine_file_h" conftest.h 2>/dev/null; then
    # The file exists and we would not be changing it
    rm -f conftest.h
  else
    rm -f "$cl_machine_file_h"
    mv conftest.h "$cl_machine_file_h"
  fi
  [$4]=1
else
  echo "creation of $cl_machine_file_h failed"
fi
rm -f conftest*
fi
else
echo "cross-compiling - cannot create $cl_machine_file_h"
fi
])dnl
dnl
## libtool.m4 - Configure libtool for the target system. -*-Shell-script-*-
## Copyright (C) 1996-1998 Free Software Foundation, Inc.
## Gordon Matzigkeit <gord@gnu.ai.mit.edu>, 1996
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
##
## As a special exception to the GNU General Public License, if you
## distribute this file as part of a program that contains a
## configuration script generated by Autoconf, you may include it under
## the same distribution terms that you use for the rest of that program.

# serial 24 AM_PROG_LIBTOOL
AC_DEFUN(AM_PROG_LIBTOOL,
[AC_REQUIRE([AM_ENABLE_SHARED])dnl
AC_REQUIRE([AM_ENABLE_STATIC])dnl
AC_REQUIRE([CL_CANONICAL_HOST])dnl
AC_REQUIRE([CL_PROG_RANLIB])dnl
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AM_PROG_LD])dnl
AC_REQUIRE([AM_PROG_NM])dnl
AC_REQUIRE([AC_PROG_LN_S])dnl
dnl
# Always use our own libtool.
LIBTOOL='$(SHELL) $(top_builddir)/libtool'
AC_SUBST(LIBTOOL)dnl

# Check for any special flags to pass to ltconfig.
libtool_flags=
test "$enable_shared" = no && libtool_flags="$libtool_flags --disable-shared"
test "$enable_static" = no && libtool_flags="$libtool_flags --disable-static"
test "$silent" = yes && libtool_flags="$libtool_flags --silent"
test "$ac_cv_prog_gcc" = yes && libtool_flags="$libtool_flags --with-gcc"
test "$ac_cv_prog_gnu_ld" = yes && libtool_flags="$libtool_flags --with-gnu-ld"

# Some flags need to be propagated to the compiler or linker for good
# libtool support.
case "$host" in
*-*-irix6*)
  # Find out which ABI we are using.
  echo '[#]line __oline__ "configure"' > conftest.$ac_ext
  if AC_TRY_EVAL(ac_compile); then
    case "`/usr/bin/file conftest.o`" in
    *32-bit*)
      LD="${LD-ld} -32"
      ;;
    *N32*)
      LD="${LD-ld} -n32"
      ;;
    *64-bit*)
      LD="${LD-ld} -64"
      ;;
    esac
  fi
  rm -rf conftest*
  ;;

*-*-sco3.2v5*)
  # On SCO OpenServer 5, we need -belf to get full-featured binaries.
  CFLAGS="$CFLAGS -belf"
  ;;
esac

# Actually configure libtool.  ac_aux_dir is where install-sh is found.
CC="$CC" CFLAGS="$CFLAGS" CPPFLAGS="$CPPFLAGS" \
LD="$LD" NM="$NM" RANLIB="$RANLIB" LN_S="$LN_S" \
${CONFIG_SHELL-/bin/sh} $ac_aux_dir/ltconfig \
$libtool_flags --no-verify $ac_aux_dir/ltmain.sh $host \
|| AC_MSG_ERROR([libtool configure failed])
])

# AM_ENABLE_SHARED - implement the --enable-shared flag
# Usage: AM_ENABLE_SHARED[(DEFAULT)]
#   Where DEFAULT is either `yes' or `no'.  If omitted, it defaults to
#   `yes'.
AC_DEFUN(AM_ENABLE_SHARED,
[define([AM_ENABLE_SHARED_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE(shared,
changequote(<<, >>)dnl
<<  --enable-shared         build shared libraries [default=>>AM_ENABLE_SHARED_DEFAULT]
changequote([, ])dnl
[  --enable-shared=PKGS    only build shared libraries if the current package
                          appears as an element in the PKGS list],
[p=${PACKAGE-default}
case "$enableval" in
yes) enable_shared=yes ;;
no) enable_shared=no ;;
*)
  enable_shared=no
  # Look at the argument we got.  We use all the common list separators.
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:,"
  for pkg in $enableval; do
    if test "X$pkg" = "X$p"; then
      enable_shared=yes
    fi
  done
  IFS="$ac_save_ifs"
  ;;
esac],
enable_shared=AM_ENABLE_SHARED_DEFAULT)dnl
])

# AM_DISABLE_SHARED - set the default shared flag to --disable-shared
AC_DEFUN(AM_DISABLE_SHARED,
[AM_ENABLE_SHARED(no)])

# AM_DISABLE_STATIC - set the default static flag to --disable-static
AC_DEFUN(AM_DISABLE_STATIC,
[AM_ENABLE_STATIC(no)])

# AM_ENABLE_STATIC - implement the --enable-static flag
# Usage: AM_ENABLE_STATIC[(DEFAULT)]
#   Where DEFAULT is either `yes' or `no'.  If omitted, it defaults to
#   `yes'.
AC_DEFUN(AM_ENABLE_STATIC,
[define([AM_ENABLE_STATIC_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE(static,
changequote(<<, >>)dnl
<<  --enable-static         build static libraries [default=>>AM_ENABLE_STATIC_DEFAULT]
changequote([, ])dnl
[  --enable-static=PKGS    only build shared libraries if the current package
                          appears as an element in the PKGS list],
[p=${PACKAGE-default}
case "$enableval" in
yes) enable_static=yes ;;
no) enable_static=no ;;
*)
  enable_static=no
  # Look at the argument we got.  We use all the common list separators.
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:,"
  for pkg in $enableval; do
    if test "X$pkg" = "X$p"; then
      enable_static=yes
    fi
  done
  IFS="$ac_save_ifs"
  ;;
esac],
enable_static=AM_ENABLE_STATIC_DEFAULT)dnl
])


# AM_PROG_LD - find the path to the GNU or non-GNU linker
AC_DEFUN(AM_PROG_LD,
[AC_ARG_WITH(gnu-ld,
[  --with-gnu-ld           assume the C compiler uses GNU ld [default=no]],
test "$withval" = no || with_gnu_ld=yes, with_gnu_ld=no)
AC_REQUIRE([AC_PROG_CC])
ac_prog=ld
if test "$ac_cv_prog_gcc" = yes; then
  # Check if gcc -print-prog-name=ld gives a path.
  AC_MSG_CHECKING([for ld used by GCC])
  ac_prog=`($CC -print-prog-name=ld) 2>&5`
  case "$ac_prog" in
  # Accept absolute paths.
  /* | [A-Za-z]:\\*)
    test -z "$LD" && LD="$ac_prog"
    ;;
  "")
    # If it fails, then pretend we aren't using GCC.
    ac_prog=ld
    ;;
  *)
    # If it is relative, then search for the first ld in PATH.
    with_gnu_ld=unknown
    ;;
  esac
elif test "$with_gnu_ld" = yes; then
  AC_MSG_CHECKING([for GNU ld])
else
  AC_MSG_CHECKING([for non-GNU ld])
fi
AC_CACHE_VAL(ac_cv_path_LD,
[if test -z "$LD"; then
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:"
  for ac_dir in $PATH; do
    test -z "$ac_dir" && ac_dir=.
    if test -f "$ac_dir/$ac_prog"; then
      ac_cv_path_LD="$ac_dir/$ac_prog"
      # Check to see if the program is GNU ld.  I'd rather use --version,
      # but apparently some GNU ld's only accept -v.
      # Break only if it was the GNU/non-GNU ld that we prefer.
      if "$ac_cv_path_LD" -v 2>&1 < /dev/null | egrep '(GNU|with BFD)' > /dev/null; then
	test "$with_gnu_ld" != no && break
      else
        test "$with_gnu_ld" != yes && break
      fi
    fi
  done
  IFS="$ac_save_ifs"
else
  ac_cv_path_LD="$LD" # Let the user override the test with a path.
fi])
LD="$ac_cv_path_LD"
if test -n "$LD"; then
  AC_MSG_RESULT($LD)
else
  AC_MSG_RESULT(no)
fi
test -z "$LD" && AC_MSG_ERROR([no acceptable ld found in \$PATH])
AC_SUBST(LD)
AM_PROG_LD_GNU
])

AC_DEFUN(AM_PROG_LD_GNU,
[AC_CACHE_CHECK([if the linker ($LD) is GNU ld], ac_cv_prog_gnu_ld,
[# I'd rather use --version here, but apparently some GNU ld's only accept -v.
if $LD -v 2>&1 </dev/null | egrep '(GNU|with BFD)' 1>&5; then
  ac_cv_prog_gnu_ld=yes
else
  ac_cv_prog_gnu_ld=no
fi])
])

# AM_PROG_NM - find the path to a BSD-compatible name lister
AC_DEFUN(AM_PROG_NM,
[AC_MSG_CHECKING([for BSD-compatible nm])
AC_CACHE_VAL(ac_cv_path_NM,
[case "$NM" in
/* | [A-Za-z]:\\*)
  ac_cv_path_NM="$NM" # Let the user override the test with a path.
  ;;
*)
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:"
  for ac_dir in /usr/ucb /usr/ccs/bin $PATH /bin; do
    test -z "$ac_dir" && ac_dir=.
    if test -f $ac_dir/nm; then
      # Check to see if the nm accepts a BSD-compat flag.
      # Adding the `sed 1q' prevents false positives on HP-UX, which says:
      #   nm: unknown option "B" ignored
      if ($ac_dir/nm -B /dev/null 2>&1 | sed '1q'; exit 0) | egrep /dev/null >/dev/null; then
        ac_cv_path_NM="$ac_dir/nm -B"
      elif ($ac_dir/nm -p /dev/null 2>&1 | sed '1q'; exit 0) | egrep /dev/null >/dev/null; then
        ac_cv_path_NM="$ac_dir/nm -p"
      else
        ac_cv_path_NM="$ac_dir/nm"
      fi
      break
    fi
  done
  IFS="$ac_save_ifs"
  test -z "$ac_cv_path_NM" && ac_cv_path_NM=nm
  ;;
esac])
NM="$ac_cv_path_NM"
AC_MSG_RESULT([$NM])
AC_SUBST(NM)
])
