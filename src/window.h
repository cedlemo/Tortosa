#ifndef WINDOW_H
#define WINDOW_H
#include <gtk/gtk.h>
#include "backbone.h"
gboolean init_window_visual_with_alpha( GtkWidget *, backbone_t *);
gboolean draw_window_background(GtkWidget *, cairo_t *, backbone_t * );
void toggle_above_below(backbone_t * );
void toggle_fullscreen(backbone_t *);
void toggle_iconify(backbone_t *);
void toggle_stick(backbone_t *);
void toggle_maximize(backbone_t *);
void grab_move_window(backbone_t *);
void reload_css_theme(backbone_t *);
void apply_window_configuration(GtkWidget *, backbone_t *);
gboolean reload_window_configuration(backbone_t *);
gboolean display_css_error_parsing(GtkCssProvider *, GtkCssSection  *, GError *, backbone_t * backbone);
#endif
