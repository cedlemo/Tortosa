#ifndef TGREGEX_H
#define TGREGEX_H
#include <vte/vte.h>
#include "backbone.h"
GString * get_flavor_string(int flavor); 
void precompile_regex(backbone_t *); 
void add_regexes_to_vte(GtkWidget *, backbone_t *);
void add_regexes_to_tab(GtkWidget *, backbone_t *);
gchar * get_regex_match_on_button_press(GtkWidget *, GdkEventButton *, int *, backbone_t *);
gchar * get_regex_match_for_tab_on_button_press(GtkWidget *, GdkEventButton *, int *, backbone_t *);
#endif
