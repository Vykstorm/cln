# Configure paths for CLN
# Richard Kreckel 11/17/2000
# stolen from Christian Bauer
# stolen from Sam Lantinga
# stolen from Manish Singh
# stolen back from Frank Belew
# stolen from Manish Singh
# Shamelessly stolen from Owen Taylor

dnl AC_PATH_LIBCLN([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl Test for installed CLN library, and define LIBCLN_CPPFLAGS and LIBCLN_LIBS
dnl
AC_DEFUN(AC_PATH_LIBCLN,
[dnl 
dnl Get the cppflags and libraries from the cln-config script
dnl
AC_ARG_WITH(cln-prefix,[  --with-cln-prefix=PFX   Prefix where CLN is installed (optional)],
            cln_config_prefix="$withval", cln_config_prefix="")
AC_ARG_WITH(cln-exec-prefix,[  --with-cln-exec-prefix=PFX Exec prefix where CLN is installed (optional)],
            cln_config_exec_prefix="$withval", cln_config_exec_prefix="")
AC_ARG_ENABLE(clntest, [  --disable-clntest       Do not try to compile and run a test CLN program],
		    , enable_clntest=yes)

  if test x$cln_config_exec_prefix != x ; then
     cln_config_args="$cln_config_args --exec-prefix=$cln_config_exec_prefix"
     if test x${CLN_CONFIG+set} != xset ; then
        CLN_CONFIG=$cln_config_exec_prefix/bin/cln-config
     fi
  fi
  if test x$cln_config_prefix != x ; then
     cln_config_args="$cln_config_args --prefix=$cln_config_prefix"
     if test x${CLN_CONFIG+set} != xset ; then
        CLN_CONFIG=$cln_config_prefix/bin/cln-config
     fi
  fi

  AC_PATH_PROG(CLN_CONFIG, cln-config, no)
  min_cln_version=ifelse([$1], ,1.1.0,$1)
  AC_MSG_CHECKING(for CLN - version >= $min_cln_version)
  no_cln=""
  if test "$CLN_CONFIG" = "no" ; then
    no_cln=yes
  else
    LIBCLN_CPPFLAGS=`$CLN_CONFIG $cln_config_args --cppflags`
    LIBCLN_LIBS=`$CLN_CONFIG $cln_config_args --libs`
    cln_config_major_version=`$CLN_CONFIG $cln_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    cln_config_minor_version=`$CLN_CONFIG $cln_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    cln_config_micro_version=`$CLN_CONFIG $cln_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_clntest" = "xyes" ; then
      ac_save_CPPFLAGS="$CPPFLAGS"
      ac_save_LIBS="$LIBS"
      CPPFLAGS="$CPPFLAGS $LIBCLN_CPPFLAGS"
      LIBS="$LIBS $LIBCLN_LIBS"
dnl
dnl Now check if the installed CLN is sufficiently new. (Also sanity
dnl checks the results of cln-config to some extent
dnl
      rm -f conf.clntest
      AC_TRY_RUN([
#include <stdio.h>
#include <string.h>
#include <cln/config.h>

/* we do not #include <stdlib.h> because autoconf in C++ mode inserts a
   prototype for exit() that conflicts with the one in stdlib.h */
extern "C" int system(const char *);

char* my_strdup (char *str)
{
  char *new_str;

  if (str) {
    new_str = new char[(strlen (str) + 1) * sizeof(char)];
    strcpy (new_str, str);
  } else
    new_str = NULL;

  return new_str;
}

int main()
{
  int major, minor, micro;
  char *tmp_version;

  system("touch conf.clntest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = my_strdup("$min_cln_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_cln_version");
     return 1;
  }

  if (($cln_config_major_version > major) ||
     (($cln_config_major_version == major) && ($cln_config_minor_version > minor)) ||
     (($cln_config_major_version == major) && ($cln_config_minor_version == minor) && ($cln_config_micro_version >= micro))) {
    if ((CL_VERSION_MAJOR == $cln_config_major_version) &&
        (CL_VERSION_MINOR == $cln_config_minor_version) &&
        (CL_VERSION_PATCHLEVEL == $cln_config_micro_version)) {
      return 0;
    } else {
      printf("\n*** 'cln-config --version' returned %d.%d.%d, but the header file I found\n", $cln_config_major_version, $cln_config_minor_version, $cln_config_micro_version);
      printf("*** corresponds to %d.%d.%d. This mismatch suggests your installation of CLN\n", CL_VERSION_MAJOR, CL_VERSION_MINOR, CL_VERSION_PATCHLEVEL);
      printf("*** is corrupted. Please inquire and consider reinstalling CLN.\n");
      return 1;
    }
  } else {
    printf("\n*** 'cln-config --version' returned %d.%d.%d, but the minimum version\n", $cln_config_major_version, $cln_config_minor_version, $cln_config_micro_version);
    printf("*** of CLN required is %d.%d.%d. If cln-config is correct, then it is\n", major, minor, micro);
    printf("*** best to upgrade to the required version.\n");
    printf("*** If cln-config was wrong, set the environment variable CLN_CONFIG\n");
    printf("*** to point to the correct copy of cln-config, and remove the file\n");
    printf("*** config.cache before re-running configure\n");
    return 1;
  }
}
],, no_cln=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       CPPFLAGS="$ac_save_CPPFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_cln" = x ; then
     AC_MSG_RESULT([yes, `$CLN_CONFIG --version`])
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$CLN_CONFIG" = "no" ; then
       echo "*** The cln-config script installed by CLN could not be found"
       echo "*** If CLN was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the CLN_CONFIG environment variable to the"
       echo "*** full path to cln-config."
     else
       if test -f conf.clntest ; then
        :
       else
          echo "*** Could not run CLN test program, checking why..."
          CPPFLAGS="$CFLAGS $LIBCLN_CPPFLAGS"
          LIBS="$LIBS $LIBCLN_LIBS"
          AC_TRY_LINK([
#include <stdio.h>
#include <cln/cln.h>
],      [ return 0; ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding CLN or finding the wrong"
          echo "*** version of CLN. If it is not finding CLN, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means CLN was incorrectly installed"
          echo "*** or that you have moved CLN since it was installed. In the latter case, you"
          echo "*** may want to edit the cln-config script: $CLN_CONFIG" ])
          CPPFLAGS="$ac_save_CPPFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     LIBCLN_CPPFLAGS=""
     LIBCLN_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(LIBCLN_CPPFLAGS)
  AC_SUBST(LIBCLN_LIBS)
  rm -f conf.clntest
])
