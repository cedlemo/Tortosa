#include <stdlib.h>
#include <gtk/gtk.h>
#include "fonts.h"
#include "dbg.h"

/*font ruby class*/
static void c_font_struct_free(font_t *f)
{
  if(f)
  {
    if(f->str) 
      g_string_free(f->str, TRUE);
    pango_font_description_free(f->desc);
    ruby_xfree(f);
  }
}
static VALUE c_font_struct_alloc( VALUE klass)
{
  return Data_Wrap_Struct(klass, NULL, c_font_struct_free, ruby_xmalloc(sizeof(font_t)));
}
static VALUE c_font_initialize(VALUE self, VALUE font)
{
  font_t *f;
  Data_Get_Struct(self, font_t, f);
  if(TYPE(font) != T_STRING)
    return Qnil;
  f->desc = pango_font_description_from_string(RSTRING_PTR(font));
  if( f->desc )
  {
    f->str = g_string_new(StringValueCStr(font));
    return self;
  }
  else
  {
    f->str = NULL;
    return Qnil;
  }
}
// TODO finish method to_s
static VALUE c_font_to_string(VALUE self)
{
  font_t *f;
  Data_Get_Struct(self, font_t, f);
  return rb_str_new2(f->str->str);
}
VALUE generate_font_ruby_class_under(VALUE module)
{
  VALUE c_font = rb_define_class_under(module, "Font", rb_cObject);
  rb_define_alloc_func(c_font, c_font_struct_alloc);
  rb_define_method(c_font, "initialize", RUBY_METHOD_FUNC(c_font_initialize), 1);
  rb_define_method(c_font, "to_s", RUBY_METHOD_FUNC(c_font_to_string), 0);
  return c_font;
}
