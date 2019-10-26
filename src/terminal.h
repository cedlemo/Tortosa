#ifndef TORTOSA_TERMINAL_H
#define TORTOSA_TERMINAL_H
#include <stdlib.h>
#include <gtk/gtk.h>
#include <vte/vte.h>
#include "dbg.h"

#define FOREGROUND "#ebdbb2"
#define BACKGROUND "#282828"
#define COLOR0 "#282828"
#define COLOR1 "#cc241d"
#define COLOR2 "#98971a"
#define COLOR3 "#d79921"
#define COLOR4 "#458588"
#define COLOR5 "#b16286"
#define COLOR6 "#689d6a"
#define COLOR7 "#a89984"
#define COLOR8 "#928374"
#define COLOR9 "#fb4934"
#define COLOR10 "#b8bb26"
#define COLOR11 "#fabd2f"
#define COLOR12 "#83a598"
#define COLOR13 "#d3869b"
#define COLOR14 "#8ec07c"
#define COLOR15 "#ebdbb2"
#define PALETTE_SIZE 16

GtkWidget * tortosa_terminal_new (void);
#endif /* !TORTOSA_TERMINAL_H */
