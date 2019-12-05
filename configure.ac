#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([pup], [1.0], [vladimir@stupin.su])
AC_COPYRIGHT([(C) 2010-2013 Vladimir Alekseyevich Stupin <vladimir@stupin.su>])
#AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC_C99
AC_PROG_MAKE_SET
AM_MAINTAINER_MODE
# Checks for libraries.
AC_CHECK_LIB(m,pow)
AC_CHECK_LIB(z,gzread)

# Checks for header files.
AC_CHECK_HEADERS([math.h string.h zlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
#   doc/Makefile
#   src/Makefile

AC_OUTPUT
