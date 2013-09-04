#include "backbone.h"

#ifndef MENUS_H
#define MENUS_H
void create_main_menu(backbone_t *);
void display_main_menu(guint32, backbone_t *, gchar *, int);
void create_reload_menu(backbone_t *);
void create_resize_menu(backbone_t *);
void display_resize_menu(guint32, backbone_t *);
#endif
