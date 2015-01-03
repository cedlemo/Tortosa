#ifndef COLORS_H
#define COLORS_H
#include <gtk/gtk.h>
#include <ruby.h>
typedef struct font_t {
  GString * str;
  PangoFontDescription * desc;
} font_t;
VALUE generate_font_ruby_class_under(VALUE);
#endif
