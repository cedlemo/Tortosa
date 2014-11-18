#include "backbone.h"

#ifndef GEARS_H
#define GEARS_H

#define FREE_GSTRING(S) if(S != NULL) g_string_free(S, TRUE)

void free_backbone( backbone_t *);
void quit_gracefully( backbone_t *);
#endif
