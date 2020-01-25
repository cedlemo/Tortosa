AM_CPPFLAGS = -DDATADIR=\"$(datadir)\"
AUTOMAKE_OPTIONS = foreign
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing compile src/Makefile.in
SUBDIRS=src test data

datadir=@prefix@/share/@PACKAGE@
filesdir = @prefix@/share/@PACKAGE@

.PHONY: launch
launch:
	G_MESSAGES_DEBUG=all ./src/tortosa

.PHONY: gresources
gresources:
	glib-compile-resources --generate-source --target=src/resources.c --sourcedir data/ data/tortosa.gresource.xml
