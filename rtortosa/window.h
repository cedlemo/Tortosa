#include <gtk/gtk.h>
#include "backbone.h"

#ifndef WINDOW_H
#define WINDOW_H

gboolean init_window_visual_with_alpha( GtkWidget *, backbone_t *);
gboolean draw_window_background(GtkWidget *, cairo_t *, backbone_t * );
#endif
