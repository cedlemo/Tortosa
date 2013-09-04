#include <vte/vte.h>
#include "backbone.h"

#ifndef TGREGEX_H
#define TGREGEX_H
GString * get_flavor_string(int flavor); 
void precompile_regex(backbone_t *); 
void add_regexes_to_tab(GtkWidget *, backbone_t *);
gchar * get_regex_match_for_tab_on_button_press(GtkWidget *, GdkEventButton *, int *, backbone_t *);
void compile_css_regexes(backbone_t * backbone);
GString * get_css_regex_match(GRegex *, const gchar *);
#endif
