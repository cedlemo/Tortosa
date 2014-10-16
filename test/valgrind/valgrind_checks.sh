#!/usr/bin/sh
__ORIGIN__=$(pwd)
__FILE__="${BASH_SOURCE[0]}"
__DIR__="$(dirname $__FILE__)"
cd $__DIR__
#VALGRIND_COMMAND="valgrind --tool=memcheck --suppressions=gtk.suppression --leak-check=full --leak-resolution=high --num-callers=20 --log-file=./vgdump"
VALGRIND_COMMAND="valgrind --tool=memcheck --suppressions=GNOME.supp/gtk3.supp --leak-check=full --leak-resolution=high --num-callers=20 --log-file=./vgdump"
printf "running : $VALGRIND_COMMAND\n"
$VALGRIND_COMMAND ./../../src/tortosa
cd $__ORIGIN
