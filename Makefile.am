AUTOMAKE_OPTIONS = foreign
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing compile src/Makefile.in
SUBDIRS=src test

.PHONY: launch
launch:
	G_MESSAGES_DEBUG=all ./src/tortosa
