#include "backbone.h"

#ifndef GEARS_H
#define GEARS_H

#define FREE_GSTRING(S) if(S != NULL) g_string_free(S, TRUE)

//backbone_t * new_backbone(void);
void free_backbone( backbone_t *);
void quit_gracefully( backbone_t *);
//void set_default_config(backbone_t *);
//gboolean window_manager_is_gnome_like(GdkScreen *);
#endif
