#ifndef FONTS_H
#define FONTS_H
#include <gtk/gtk.h>
#include "backbone.h"
#include <ruby.h>
typedef struct font_t {
  GString * font;
  PangoFontDescription * desc;
} font_t;

VALUE generate_font_ruby_class_under(VALUE);
#endif
