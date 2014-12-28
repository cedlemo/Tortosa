#ifndef COLORS_H
#define COLORS_H
#include <gtk/gtk.h>
#include <ruby.h>
typedef struct color_t {
	GString * color;
	GdkRGBA rgba;
} color_t;
gboolean extended_gdk_rgba_parse (GdkRGBA *,  const gchar *);
VALUE generate_color_ruby_class_under(VALUE);
#endif
