#include <gtk/gtk.h>
#include "backbone.h"

#ifndef WINDOW_H
#define WINDOW_H

gboolean init_window_visual_with_alpha( GtkWidget *, backbone_t *);
gboolean draw_window_background(GtkWidget *, cairo_t *, backbone_t * );
//gboolean get_window_state(GtkWidget*, GdkEventWindowState *, backbone_t *);
//void apply_window_configuration(GtkWidget *, backbone_t *);
#endif
