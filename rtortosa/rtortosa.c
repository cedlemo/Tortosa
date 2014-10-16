#include <ruby.h>
#include <gtk/gtk.h>
#include "gears.h"
#include "window.h"
#include "colors.h"
#include "backbone.h"
#include "stdio.h"

backbone_t backbone;

static  VALUE rtortosa_initialize( VALUE self, VALUE args)
{
  // TODO try to handle args gtk_init(&argc, &argv);
  //if(TYPE(args) != T_ARRAY)
    gtk_init(NULL, NULL);
  //else
  //{
  //  int argc = ;
  //  char * argv;  
  //}
  backbone.display = gdk_display_get_default ();
  backbone.screen = gdk_display_get_default_screen (backbone.display);

  /***************/ 
  /* Main Window */
  /***************/
  backbone.window.title = g_string_new("Tortosa Terminal");
  backbone.window.wm_class = g_string_new("Tortosa");
  backbone.window.wm_name = g_string_new("Tortosa");
  backbone.window.role = g_string_new("Tortosa");
  backbone.window.background.color = g_string_new("#00000000");
  extended_gdk_rgba_parse(&backbone.window.background.rgba, backbone.window.background.color->str);
  backbone.window.decorated = TRUE;
  backbone.window.width = 0;
  backbone.window.height = 0;

  backbone.window.widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_icon_name("terminal");
  //set window transparent if system supports it:
  init_window_visual_with_alpha(backbone.window.widget, &backbone);
  apply_window_configuration(backbone.window.widget, &backbone);
  
  g_signal_connect_swapped(backbone.window.widget, "destroy", G_CALLBACK(quit_gracefully), &backbone); 
  g_signal_connect(backbone.window.widget, "window-state-event", G_CALLBACK(get_window_state), &backbone); //get window state events, this is used by fullscreen, above/below, iconify, maximize ... actions  
  g_signal_connect(G_OBJECT(backbone.window.widget), "draw", G_CALLBACK(draw_window_background), &backbone); //redraw window background when needed
  g_signal_connect(backbone.window.widget, "screen-changed", G_CALLBACK(init_window_visual_with_alpha), &backbone); //re-define the visual of the window if this one move to another screen
  return self;
}
static VALUE rtortosa_run( VALUE self)
{
  gtk_widget_show_all(backbone.window.widget);
  gtk_main();

  return Qnil;
}
static VALUE rtortosa_set_height( VALUE self, VALUE height)
{
  if( TYPE(height) != T_FIXNUM)
    return Qnil;
  backbone.window.height = FIX2INT(height);
  if( backbone.window.width > 0 && backbone.window.height > 0)
    gtk_window_resize (GTK_WINDOW(backbone.window.widget), backbone.window.width, backbone.window.height);
}
static VALUE rtortosa_set_width( VALUE self, VALUE width)
{
  if( TYPE(width) != T_FIXNUM)
    return Qnil;
  backbone.window.width = FIX2INT(width);
  if( backbone.window.width > 0 && backbone.window.height > 0)
    gtk_window_resize (GTK_WINDOW(backbone.window.widget), backbone.window.width, backbone.window.height);
}
static VALUE rtortosa_set_background_color( VALUE self, VALUE color)
{
  color_t *c;
  Data_Get_Struct(color, color_t, c);
  backbone.window.background.color = g_string_new(c->color->str);
  backbone.window.background.rgba.red = c->rgba.red;
  backbone.window.background.rgba.green = c->rgba.green;
  backbone.window.background.rgba.blue = c->rgba.blue;
  backbone.window.background.rgba.alpha = c->rgba.alpha;
  gtk_widget_queue_draw(backbone.window.widget);
  return Qnil;  
}

static void c_color_struct_free(color_t *c)
{
  if(c)
  {
    if(c->color) {g_string_free(c->color, TRUE);}
    ruby_xfree(c);
  }
}
static VALUE c_color_struct_alloc( VALUE klass)
{
  return Data_Wrap_Struct(klass, NULL, c_color_struct_free, ruby_xmalloc(sizeof(color_t)));
}
static VALUE c_color_initialize(VALUE self, VALUE color)
{
  color_t *c;
  Data_Get_Struct(self, color_t, c);
  if(TYPE(color) != T_STRING)
    return Qnil;

  if( extended_gdk_rgba_parse(&c->rgba, RSTRING_PTR(color)) )
  {
    c->color = g_string_new(StringValueCStr(color));
    return self;
  }
  else
  {
    c->color = NULL;
    return Qnil;
  }
}
static VALUE c_color_get_color(VALUE self)
{
  color_t *c;
  Data_Get_Struct(self, color_t, c);
  return rb_str_new2(c->color->str);
}
static VALUE c_color_get_rgb_color(VALUE self)
{
  color_t *c;
  Data_Get_Struct(self, color_t, c);
  return rb_str_new2(gdk_rgba_to_string(&c->rgba));
}
static VALUE c_color_get_red(VALUE self)
{
  color_t *c;
  Data_Get_Struct(self, color_t, c);
  return DBL2NUM(c->rgba.red);
}
static VALUE c_color_get_green(VALUE self)
{
  color_t *c;
  Data_Get_Struct(self, color_t, c);
  return DBL2NUM(c->rgba.green);
}
static VALUE c_color_get_blue(VALUE self)
{
  color_t *c;
  Data_Get_Struct(self, color_t, c);
  return DBL2NUM(c->rgba.blue);
}
static VALUE c_color_get_alpha(VALUE self)
{
  color_t *c;
  Data_Get_Struct(self, color_t, c);
  return DBL2NUM(c->rgba.alpha);
}
void Init_rtortosa()
{
  VALUE m_rtortosa;
  m_rtortosa = rb_define_module("Rtortosa");
  rb_define_module_function(m_rtortosa, "init", rtortosa_initialize, 0); 
  rb_define_module_function(m_rtortosa, "run", rtortosa_run, 0);
  rb_define_module_function(m_rtortosa, "height=", rtortosa_set_height, 1);
  rb_define_module_function(m_rtortosa, "width=", rtortosa_set_width, 1);
  rb_define_module_function(m_rtortosa, "background_color=", rtortosa_set_background_color, 1);
  
  VALUE c_color = rb_define_class_under(m_rtortosa, "Color", rb_cObject);
  rb_define_alloc_func(c_color, c_color_struct_alloc);
  rb_define_method(c_color, "initialize", RUBY_METHOD_FUNC(c_color_initialize), 1);
  rb_define_method(c_color, "get_color", RUBY_METHOD_FUNC(c_color_get_color), 0);
  rb_define_method(c_color, "get_rgb_color", RUBY_METHOD_FUNC(c_color_get_rgb_color), 0);
  rb_define_method(c_color, "get_red", RUBY_METHOD_FUNC(c_color_get_red), 0);
  rb_define_method(c_color, "get_green", RUBY_METHOD_FUNC(c_color_get_green), 0);
  rb_define_method(c_color, "get_blue", RUBY_METHOD_FUNC(c_color_get_blue), 0);
  rb_define_method(c_color, "get_alpha", RUBY_METHOD_FUNC(c_color_get_alpha), 0);
}
