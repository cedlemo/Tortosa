#ifndef TABS_H
#define TABS_H
#include <gtk/gtk.h>
#include <ruby.h>
#include "backbone.h"
GtkWidget * notebook_get_current_widget(GtkNotebook *);
void go_to_next_tab(GtkNotebook *);
void go_to_prev_tab(GtkNotebook *);
#endif
