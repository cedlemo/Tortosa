gsettings_SCHEMAS = com.github.cedlemo.tortosa.gschema.xml
EXTRA_DIST = $(gsettings_SCHEMAS)

BUILT_SOURCES = 				\
	gschemas.compiled

@GSETTINGS_RULES@

gschemas.compiled: com.github.cedlemo.tortosa.gschema.xml
	$(GLIB_COMPILE_SCHEMAS) .

CLEANFILES = 					\
	gschemas.compiled
