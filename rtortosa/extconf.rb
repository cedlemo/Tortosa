require 'mkmf'
have_library('gtk-3')
have_library('vte2_90')
$CFLAGS += " " + `pkg-config --cflags vte-2.90 gtk+-3.0`.chomp
create_makefile('rtortosa')
