#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(tortosa, 0.1, cedlemo@gmx.com)
AM_INIT_AUTOMAKE


#AC_CONFIG_SRCDIR([src/gears.h])
#AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AM_PROG_CC_C_O

# Checks for libraries.
#AC_SEARCH_LIBS(vte-2.90,gtk+-3.0, [],AC_MSG_ERROR([missing libs]))
PKG_CHECK_MODULES([DEPS], [vte-2.90 gtk+-3.0 cairo])
#PKG_CHECK_MODULES([GTK3], [gtk+-3.0])

# Checks for header files.
#AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([
								Makefile
								src/Makefile
								])
AC_OUTPUT
