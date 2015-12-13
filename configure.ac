#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_CONFIG_MACRO_DIR([.])
AC_PREREQ([2.69])
AC_INIT(aussielotto, 1.0.4, dennisk@netspace.net.au)
AM_INIT_AUTOMAKE()
AC_OUTPUT(Makefile src/Makefile doc/Makefile)

AC_CONFIG_SRCDIR([src/AussieLotto.cxx])
dnl Check for FLTK
FLTK_VERSION=1.1.7
AM_PATH_FLTK($FLTK_VERSION,
         :,
         AC_MSG_ERROR([*** FLTK version >= $FLTK_VERSION not found!])
)

PKG_CHECK_MODULES(CURL, libcurl)

#LIBS="$LIBS $FLTK_LIBS"
LIBS="$LIBS"

#LDFLAGS="$LDFLAGS $FLTK_LDFLAGS"
LDFLAGS="$LDFLAGS"

AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([locale.h nl_types.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])
AC_PROG_RANLIB
AX_CHECK_COMPILE_FLAG
AX_GCC_X86_CPUID
AX_GCC_ARCHFLAG([no])
#CXXFLAGS="$CXXFLAGS $FLTK_CXXFLAGS $CFLAGS"
#CXXFLAGS="$CXXFLAGS $CFLAGS"
CXXFLAGS="$CXXFLAGS"

CFLAGS="$CFLAGS"
AC_OUTPUT(include/defs.h)
AC_OUTPUT(aussielotto.spec)
AC_OUTPUT
