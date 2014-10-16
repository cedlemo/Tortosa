#include <gtk/gtk.h>
#ifndef COLORS_H
#define COLORS_H
typedef struct color_t {
	GString * color;
	GdkRGBA rgba;
} color_t;
gboolean extended_gdk_rgba_parse (GdkRGBA *,  const gchar *);
#endif
