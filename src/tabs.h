#ifndef TABS_H
#define TABS_H
#include <gtk/gtk.h>
#include "backbone.h"
void close_tab(GtkWidget *, backbone_t *);
void go_to_next_tab( backbone_t*);
void go_to_prev_tab( backbone_t *);
void apply_tabs_configuration(backbone_t *);
void new_tab(backbone_t *);
void apply_vte_configuration(backbone_t *, GtkWidget *);
gboolean reload_vte_configuration(backbone_t *);
void apply_tab_configuration( backbone_t *);
gboolean reload_tabs_configuration( backbone_t *);
void copy_selected_text_to_clipboard(backbone_t *);
void paste_clipboard_to_vte_child(backbone_t *);
#endif
