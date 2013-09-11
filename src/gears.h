#include "backbone.h"

#ifndef GEARS_H
#define GEARS_H

#define FREE_GSTRING(S) if(S != NULL) g_string_free(S, TRUE)

backbone_t * new_backbone(void);
void free_backbone( backbone_t *);
void quit_gracefully( backbone_t *);
void init_vte_color( backbone_t * , int , char * );
gboolean load_config( backbone_t*);
void load_window_configuration(backbone_t *);
void load_tabs_configuration(backbone_t *);
void load_vte_configuration(backbone_t *);
void load_css_configuration(backbone_t *);
void load_css_regexes_match(backbone_t *);
gboolean reload_tortosa_configuration(backbone_t *);
gint find_node_by_widget ( gconstpointer, gconstpointer);
void remove_node_by_widget( GSList *, GtkWidget *);
void free_slist_and_data(GSList *);
void util_open_url(backbone_t *);
gboolean window_manager_is_gnome_like(GdkScreen *);
#endif
