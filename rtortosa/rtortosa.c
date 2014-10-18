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
  backbone.command.mode = FALSE;
  backbone.command.line = g_string_new(NULL);

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
static VALUE rtortosa_pick_a_color(VALUE self)
{
  VALUE color = Qnil;
  GtkResponseType result;


  GtkWidget *dialog = gtk_color_chooser_dialog_new("Pick a color", GTK_WINDOW(backbone.window.widget));
  result = gtk_dialog_run(GTK_DIALOG(dialog));
  if (result == GTK_RESPONSE_OK || result == GTK_RESPONSE_APPLY)
  {
    color_t *c;
    GdkRGBA rgba;
    gtk_color_chooser_set_use_alpha(GTK_COLOR_CHOOSER(dialog), TRUE);
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(dialog), &rgba);
    VALUE m_rtortosa = rb_const_get( rb_cObject, rb_intern( "Rtortosa" ) );
    VALUE cColor = rb_const_get_at( m_rtortosa, rb_intern("Color") );
    VALUE params[1];
    params[1] = rb_str_new2("#000000");
    color = rb_class_new_instance( 1, params, cColor );  
    Data_Get_Struct(color, color_t , c);
    c->color = g_string_new(gdk_rgba_to_string(&rgba));
    c->rgba.red = rgba.red;
    c->rgba.green = rgba.green;
    c->rgba.blue = rgba.blue;
    c->rgba.alpha = rgba.alpha;
   }
  gtk_widget_destroy(dialog);
  return color;
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

static ID rb_intern_wrapper( char* str) {
  return rb_intern(str);
}

static VALUE build_event_hash(GdkEventKey *event)
{
  ID etime = rb_intern_wrapper("time");
  ID state = rb_intern_wrapper("state");
  ID keyval = rb_intern_wrapper("keyval");
  ID keyname = rb_intern_wrapper("keyname");
  VALUE time_sym = ID2SYM(etime);
  VALUE state_sym = ID2SYM(state);
  VALUE keyval_sym = ID2SYM(keyval);
  VALUE keyname_sym = ID2SYM(keyname);
  VALUE e = rb_hash_new();
  rb_hash_aset(e, keyname_sym, rb_str_new2(gdk_keyval_name(event->keyval)));
  rb_hash_aset(e, time_sym, UINT2NUM(event->time));   
  rb_hash_aset(e, state_sym, UINT2NUM(event->state));   
  rb_hash_aset(e, keyval_sym, UINT2NUM(event->keyval));   
  
  return e;
}
gboolean event_key_press(GtkWidget *widget, GdkEventKey *event, void * userdata)
{
  VALUE passthrough = (VALUE) userdata;
  VALUE callbacks;
  VALUE callbacks_data;
  callbacks = rb_ary_entry(passthrough, 0);
  callbacks_data = rb_ary_entry(passthrough, 1);
  VALUE e = build_event_hash(event);
  VALUE key_event_cb_sym = ID2SYM(rb_intern("key_event_cb"));
  VALUE command_line_cb_sym = ID2SYM(rb_intern("command_line_cb"));
  VALUE key_event_cb = rb_hash_aref(callbacks, key_event_cb_sym);
  VALUE command_line_cb = rb_hash_aref(callbacks, command_line_cb_sym);
  VALUE key_event_data = rb_hash_aref(callbacks_data, key_event_cb_sym);
  VALUE command_line_data = rb_hash_aref(callbacks_data, command_line_cb_sym);
  guint(g) = event->keyval;
  /*if backbone.command.mode = TRUE
    switch(event->keyval)
    {
      case Enter:
        backbone.command_mode = FALSE
        rb_funcall(callback, rb_intern("call"), 2, command_line, e, command_line_data);
        backbone.command_string (empty g_string)
        break;
      case ESC:
        backbone.command_mode = FALSE
        backbone.command_string (empty g_string)
      case BackSpace:
        backbone.command_string =- gdk_keyval_name(event->keyval);
      default:
        backbone.command_string =+ gdk_keyval_name(event->keyval);
    }*/  
  if(backbone.command.mode == TRUE)
  {
    switch(g) {
      case GDK_KEY_Return: {
        backbone.command.mode = FALSE;
        VALUE command_line = rb_str_new2(backbone.command.line->str);
        rb_funcall(command_line_cb, rb_intern("call"), 3, command_line, e, command_line_data);    
        g_string_erase(backbone.command.line,0,-1);
        break;
      }
      case GDK_KEY_Escape: {
        backbone.command.mode = FALSE;
        g_string_erase(backbone.command.line,0,-1);
        break;
      }
      case GDK_KEY_BackSpace: {
        g_string_erase(backbone.command.line,backbone.command.line->len,1);
        break;
      }
      default: {
        //char c = (char) gdk_keyval_to_unicode(event->keyval);
        //g_string_append(backbone.command.line, gdk_keyval_name(event->keyval));
        g_string_append_unichar(backbone.command.line, gdk_keyval_to_unicode(event->keyval));
        /*else if Ctrl+shift+c 
        backbone.command_mode = TRUE*/ 
        break;
      }
      return TRUE;
    }
  }
  else if ((event->state & (GDK_CONTROL_MASK|GDK_SHIFT_MASK)) == (GDK_CONTROL_MASK|GDK_SHIFT_MASK)) 
  {
    if (g == GDK_KEY_C) {
      backbone.command.mode = TRUE;
      return TRUE;
    }
  }
  if(key_event_cb != Qnil)
    rb_funcall(key_event_cb, rb_intern("call"), 2, e, key_event_data);

  return FALSE;
}
/*Take 2 hash:
  callbacks = {:key_event_cb => callback, :command_line_cb => callback}
  userdata = {:key_event_cb => data , :command_line_cb => data}
*/
static VALUE rtortosa_on_key_press_event(VALUE self, VALUE callbacks, VALUE userdata)
{
  VALUE passthrough;
  if( (TYPE(callbacks) != T_HASH) && ( TYPE(userdata) != T_HASH ))
    rb_raise(rb_eTypeError, "Pack evrything in a hash");
  
  VALUE key_event_cb_sym = ID2SYM(rb_intern("key_event_cb"));
  VALUE command_line_cb_sym = ID2SYM(rb_intern("command_line_cb"));
  VALUE key_event_cb = rb_hash_aref(callbacks, key_event_cb_sym);
  VALUE command_line_cb = rb_hash_aref(callbacks, command_line_cb_sym);

  if( (command_line_cb == Qnil) && (key_event_cb == Qnil))
    return Qnil;
  
  if((key_event_cb != Qnil) && (rb_class_of(key_event_cb) != rb_cProc))
    rb_raise(rb_eTypeError, "Expected Proc callback");

  if((command_line_cb != Qnil) && (rb_class_of(command_line_cb) != rb_cProc))
    rb_raise(rb_eTypeError, "Expected Proc callback");

  passthrough = rb_ary_new();
  rb_ary_store(passthrough, 0, callbacks);
  rb_ary_store(passthrough, 1, userdata);  
  g_signal_connect( backbone.window.widget, 
                    "key-press-event", 
                    G_CALLBACK(event_key_press),
                    (void *) passthrough);
  return Qnil;
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
  rb_define_module_function(m_rtortosa, "on_key_press_event", rtortosa_on_key_press_event, 2);
  rb_define_module_function(m_rtortosa, "pick_a_color", rtortosa_pick_a_color, 0);
  
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
