AC_INIT([Tortosa], 2.0)
AM_INIT_AUTOMAKE
AC_PROG_CC

PKG_CHECK_MODULES([DEPS], [vte-2.91 gtk+-3.0 libpcre2-32])
PKG_CHECK_MODULES([DEV_DEPS], [vte-2.91 gtk+-3.0 cmocka])

GLIB_GSETTINGS

AC_CONFIG_FILES([
		 Makefile
		 src/Makefile
		 test/Makefile
		 data/Makefile
		 ])

AC_OUTPUT
