#include "backbone.h"
#include <limits.h>
#ifndef GEARS_H
#define GEARS_H

#define FREE_GSTRING(S) if(S != NULL) g_string_free(S, TRUE)

void free_backbone( backbone_t *);
void quit_gracefully( backbone_t *);
void widget_set_transparent_background(GtkWidget *);
uint32_t uint2uint32(unsigned int);
uint16_t uint2uint16(unsigned int);
uint8_t uint2uint8(unsigned int);
int32_t int2int32(int);
int16_t int2int16(int);
int8_t int2int8(int);
#endif
