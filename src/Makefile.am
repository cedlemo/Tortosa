AM_CPPFLAGS = -DG_LOG_DOMAIN=\"Tortosa\"
bin_PROGRAMS = tortosa
tortosa_LDFLAGS = $(DEPS_LIBS)
tortosa_CPPFLAGS = $(DEPS_CFLAGS) $(AM_CPPFLAGS)  -DDATADIR=\"$(datadir)\"

tortosa_SOURCES = tortosa.c application.c terminal.c shell.c window.c header-bar.c notebook.c resources.c preferences.c event-label.c
