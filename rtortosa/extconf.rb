require 'mkmf'
have_library('gtk-3')
#have_library('vte3')
$LIBS += " " + `pkg-config --libs vte-2.91 gtk+-3.0`.chomp
$CFLAGS += " " + `pkg-config --cflags vte-2.91 gtk+-3.0`.chomp
create_makefile('rtortosa')
