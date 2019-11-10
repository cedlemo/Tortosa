# Tortosa

Vte Terminal Emulator

## Expected Functionnalities

### Done
* Window with a terminal
* Css theming for all the widgets
* Setup unit testing environment

### To Do
* Enforce a coding style (use clang linter ?)
* define rules to memory managment
* add an application menu
* Window with multiple terminals managment
  - multiple terminals in tabs (one terminal in one tab, GtkNotebook)
  - multiple terminals in pans (multiple terminal in one tab)
  - add shortcuts to manage tabs
* Terminal colors / Palette managment
* GSettings
  - specify the Css theme file
  - specify the shell to use
  - specify the Palette color
  - specify the Vte configuration
* Vte Regexp + actions
* Unit testing

## Development Notes

### Build, clean test:

* https://developer.gnome.org/anjuta-build-tutorial/stable/create-autotools.html.en
* https://developer.gnome.org/gtk3/stable/gtk-getting-started.html
* https://stackoverflow.com/questions/10999549/how-do-i-create-a-configure-script

```bash
aclocal
automake --add-missing --foreign
autoconf
./configure
make
./src/tortosa
```
Use `sh build.sh`

Launch tortosa to test it:

```
make launch
```

Clean the repository after build:

```bash
make clean
make maintainer-clean
```

Generates the compile_commands.json for ccls/clang used with coc.

```bash
# after having buildt everything
bear make
```

### Debug

#### Gdb

#### Valgrind:

* https://developer.gnome.org/programming-guidelines/stable/tooling.html.en#valgrind
* http://liacs.leidenuniv.nl/~stefanovtp/courses/StudentenSeminarium/Papers/OS/IMMG.pdf

```bash
libtool exec valgrind --tool=memcheck --leak-check=full --suppressions=./gtk.supp ./src/tortosa
G_SLICE=debug-blocks valgrind --tool=memcheck --leak-check=full --suppressions=./gtk.supp ./src/tortos
```

* G_SLICE=debug-blocks will turn off gtk's advanced memory management to allow valgrind to show correct results.
* --leak-check=full will show stack traces for the leaked memory blocks.
* You can also use --show-reachable=yes to see stack traces for all memory blocks that haven't been free when the program exits.
* There is also the massif valgrind tool that tracks memory usage to show which parts of the program are using the most memory.

Run program under massif:

```
G_SLICE=always-malloc valgrind --tool=massif --detailed-freq=2 --max-snapshots=400 --num-callers=20 ./src/tortosa
```

## Global Structure:

### Classes hierarchy

The structure should be the following:

```
TortosaApplication
    |
     ---> TortosaWindowApplication
             |
	      ---> TortosaHeaderBar
	     |
	      ---> TortosaNotebook
	      		|
			 ---> TortosaTab (1 to n)
			       |
			        ---> TortosaPan (1 to n)
```

### Tortosa Shell

The application uses a single instance of a TortosaShell class to store all of its runtime information. This
 instance is stored as a global variable and is accessible in all the different parts of the code thanks to the
 `tortosa_shell_get_default` constructor which implements the singleton pattern.

This design is shamelessly stolen from Epiphany:

    * https://gitlab.gnome.org/GNOME/epiphany/blob/master/HACKING.md
    * https://gitlab.gnome.org/GNOME/epiphany/blob/master/src/ephy-shell.h
    * https://gitlab.gnome.org/GNOME/epiphany/blob/master/src/ephy-shell.c


