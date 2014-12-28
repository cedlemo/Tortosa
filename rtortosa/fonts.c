#include "fonts.h"
/*
typedef struct font_t {
  GString * font;
  PangoFontDescription * desc;
} font_t;
*/
static void c_font_struct_free(font_t *f)
{
  if(f)
  {
    if(f->font)
      g_string_free(f->font, TRUE);
    if(f->desc)
      pango_font_description_free(f->desc);
    ruby_xfree(f);
  }
}
static VALUE c_font_struct_alloc(VALUE klass)
{
  return Data_Wrap_Struct(klass, NULL, c_font_struct_free, ruby_xmalloc(sizeof(font_t)));
}
static VALUE c_font_initialize(VALUE self, VALUE font)
{
  font_t *f;
  Data_Get_Struct(self, font_t, f);
  if(TYPE(font) != T_STRING)
    rb_raise(rb_eTypeError, "Expected a string");
  f->desc = pango_font_description_from_string( RSTRING_PTR(font));
  if(f->desc)
  {
    f->font = g_string_new(pango_font_description_to_string(f->desc));
    return self;
  }
  else
  {
    f->font =NULL;
    return Qnil;
  }
}
static VALUE c_font_get_font_description(VALUE self)
{
  font_t *f;
  Data_Get_Struct(self, font_t,f); 
  return rb_str_new2(f->font->str);
}
static VALUE c_font_set_font_description(VALUE self, VALUE font)
{
  font_t *f;
  Data_Get_Struct(self, font_t, f);
  if(TYPE(font) != T_STRING)
    rb_raise(rb_eTypeError, "Expected a string");
  f->desc = pango_font_description_from_string( RSTRING_PTR(font));
  if(f->desc)
  {
    f->font = g_string_new(pango_font_description_to_string(f->desc));
    return self;
  }
  else
  {
    f->font =NULL;
    return Qnil;
  }
}
VALUE generate_font_ruby_class_under(VALUE module)
{
  VALUE c_font = rb_define_class_under(module, "Font", rb_cObject);
  rb_define_alloc_func(c_font, c_font_struct_alloc);
  rb_define_method(c_font, "initialize", RUBY_METHOD_FUNC(c_font_initialize), 1);
  rb_define_method(c_font, "get_font_description", RUBY_METHOD_FUNC(c_font_get_font_description), 0);
  rb_define_method(c_font, "set_font_description", RUBY_METHOD_FUNC(c_font_set_font_description), 1);
  return c_font;
}
