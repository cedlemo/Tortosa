#include <ruby.h>
#include <gtk/gtk.h>
#include "gears.h"
#include "window.h"
#include "colors.h"
#include "backbone.h"
#include "stdio.h"
#include "gtk_window_methods.h"
#include "gtk_notebook_methods.h"
#include "terminal.h"
backbone_t backbone;

static gboolean default_event_key_press(GtkWidget *widget, GdkEventKey *event, void * userdata)
{
  guint(g) = event->keyval;

  if ((event->state & (GDK_CONTROL_MASK|GDK_SHIFT_MASK)) == (GDK_CONTROL_MASK|GDK_SHIFT_MASK)) 
  {
    if (g == GDK_KEY_C) {
      gtk_widget_show(backbone.window.entry);
      gtk_widget_grab_focus(backbone.window.entry);
      backbone.command.mode = TRUE;
      return TRUE;
    }
  }
  else 
  {
    if(g == GDK_KEY_Escape && backbone.command.mode){
      gtk_widget_hide(backbone.window.entry);
      gtk_widget_grab_focus(backbone.window.widget);
      backbone.command.mode = FALSE;
      return TRUE;
    }
  }
  return FALSE;
}
static  VALUE rtortosa_initialize( VALUE self, VALUE args)
{
  // TODO try to handle args gtk_init(&argc, &argv);
  if(TYPE(args) != T_ARRAY)
    gtk_init(NULL, NULL);
  else
  {
    if(RARRAY_LEN(args) == 0)
      gtk_init(NULL, NULL);
    else
    {
      int i;
      int argc = RARRAY_LEN(args);
      char * argv[argc];
      for(i=0; i<argc; i++)
      {
        if(TYPE(*(RARRAY_PTR(args)+i)) == T_STRING){
          argv[i] = RSTRING_PTR(*(RARRAY_PTR(args) + i));
        }
      }
      argc = i - 1;
      gtk_init(&argc,(char ***) &argv);
    }
  }
  backbone.display = gdk_display_get_default ();
  backbone.screen = gdk_display_get_default_screen (backbone.display);
  backbone.command.mode = FALSE;
  backbone.command.line = g_string_new(NULL);

  /***************/ 
  /* Main Window */
  /***************/
  backbone.window.background.color = g_string_new("#00000000");
  extended_gdk_rgba_parse(&backbone.window.background.rgba, backbone.window.background.color->str);

  backbone.window.widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  //set window transparent if system supports it:
  init_window_visual_with_alpha(backbone.window.widget, &backbone);
  
  g_signal_connect_swapped(backbone.window.widget, "destroy", G_CALLBACK(quit_gracefully), &backbone); 
  g_signal_connect(G_OBJECT(backbone.window.widget), "draw", G_CALLBACK(draw_window_background), &backbone); //redraw window background when needed
  g_signal_connect(backbone.window.widget, "screen-changed", G_CALLBACK(init_window_visual_with_alpha), &backbone); //re-define the visual of the window if this one move to another screen
  backbone.window.key_event_handler_id = g_signal_connect(backbone.window.widget, 
                                    "key-press-event", 
                                    G_CALLBACK(default_event_key_press), NULL);

  /***********/
  /* Vbox*/
  /***********/
  backbone.window.vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GdkRGBA transparent;
  transparent.red =0;
  transparent.green = 0;
  transparent.blue = 0;
  transparent.alpha = 0;
  gtk_widget_override_background_color(backbone.window.vbox,GTK_STATE_FLAG_NORMAL,&transparent);
  gtk_container_add(GTK_CONTAINER(backbone.window.widget), backbone.window.vbox);
  /**************/
  /*GtkNotebook */
  /**************/
  backbone.window.notebook = gtk_notebook_new(); 
  gtk_widget_override_background_color(backbone.window.notebook,GTK_STATE_FLAG_NORMAL,&transparent);
  gtk_box_pack_start(GTK_BOX(backbone.window.vbox), backbone.window.notebook, FALSE, FALSE, 0);
  
  new_terminal_emulator(&backbone);
  /***********/
  /* GtkEntry*/
  /***********/
  backbone.window.entry = gtk_entry_new();
  gtk_entry_set_has_frame(GTK_ENTRY(backbone.window.entry),FALSE);
  gtk_entry_set_activates_default(GTK_ENTRY(backbone.window.entry),TRUE);
  gtk_box_pack_end(GTK_BOX(backbone.window.vbox), backbone.window.entry, FALSE, FALSE, 0);
  
   return self;
}
static VALUE rtortosa_run( VALUE self)
{
  gtk_widget_show_all(backbone.window.widget);
  gtk_widget_hide(backbone.window.entry);
  gtk_main();

  return Qnil;
}
static VALUE rtortosa_quit(VALUE self)
{
  quit_gracefully(&backbone);
  return Qnil;
}
static VALUE rtortosa_set_background_color( VALUE self, VALUE color)
{
  color_t *c;
  Data_Get_Struct(color, color_t, c);
  if(backbone.window.background.color)
    g_string_free(backbone.window.background.color, TRUE);
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
static gboolean event_key_press(GtkWidget *widget, GdkEventKey *event, void * userdata)
{
  VALUE passthrough = (VALUE) userdata;
  VALUE callback;
  VALUE callback_data;
  callback = rb_ary_entry(passthrough, 0);
  callback_data = rb_ary_entry(passthrough, 1);
  VALUE e = build_event_hash(event);

  guint(g) = event->keyval;

  if ((event->state & (GDK_CONTROL_MASK|GDK_SHIFT_MASK)) == (GDK_CONTROL_MASK|GDK_SHIFT_MASK)) 
  {
    if (g == GDK_KEY_C) {
      gtk_widget_show(backbone.window.entry);
      gtk_widget_grab_focus(backbone.window.entry);
      backbone.command.mode = TRUE;
      return TRUE;
    }
  }
  else 
  {
    if(g == GDK_KEY_Escape && backbone.command.mode){
      gtk_widget_hide(backbone.window.entry);
      gtk_widget_grab_focus(backbone.window.widget);
      backbone.command.mode = FALSE;
      return TRUE;
    }
  }
  rb_funcall(callback, rb_intern("call"), 2, e, callback_data);
  return FALSE;
}
static VALUE rtortosa_on_key_press_event(VALUE self, VALUE callback, VALUE userdata)
{
  g_signal_handler_disconnect(backbone.window.widget,
                              backbone.window.key_event_handler_id);
  VALUE passthrough;
  
  if((callback != Qnil) && (rb_class_of(callback) != rb_cProc))
    rb_raise(rb_eTypeError, "Expected Proc callback");

  passthrough = rb_ary_new();
  rb_ary_store(passthrough, 0, callback);
  rb_ary_store(passthrough, 1, userdata);  
  backbone.window.key_event_handler_id = g_signal_connect( backbone.window.widget, 
                    "key-press-event", 
                    G_CALLBACK(event_key_press),
                    (void *) passthrough);
  return Qnil;
}
static void parse_command_line(GtkEntry *entry, void *userdata)
{
  VALUE passthrough = (VALUE) userdata;
  VALUE callback;
  VALUE callback_data;
  callback = rb_ary_entry(passthrough, 0);
  callback_data = rb_ary_entry(passthrough, 1);
  VALUE command_line = rb_str_new2(gtk_entry_get_text(GTK_ENTRY(backbone.window.entry)));
  rb_funcall(callback, rb_intern("call"), 2, command_line, callback_data); 

}
static VALUE rtortosa_on_entry_validate_event(VALUE self, VALUE callback, VALUE userdata)
{
  VALUE passthrough;
  
  if(rb_class_of(callback) != rb_cProc)
    rb_raise(rb_eTypeError, "Expected Proc callback");

  passthrough = rb_ary_new();
  rb_ary_store(passthrough, 0, callback);
  rb_ary_store(passthrough, 1, userdata);  
  g_signal_connect( backbone.window.entry, 
                    "activate", 
                    G_CALLBACK(parse_command_line),
                    (void *) passthrough);
  return Qnil;
}
void Init_rtortosa()
{
  VALUE m_rtortosa;
  m_rtortosa = rb_define_module("Rtortosa");
  rb_define_module_function(m_rtortosa, "init", rtortosa_initialize, 1); 
  rb_define_module_function(m_rtortosa, "run", rtortosa_run, 0);
  rb_define_module_function(m_rtortosa, "quit", rtortosa_quit, 0);
  rb_define_module_function(m_rtortosa, "background_color=", rtortosa_set_background_color, 1);
  rb_define_module_function(m_rtortosa, "on_command_line_event", rtortosa_on_entry_validate_event, 2);
  rb_define_module_function(m_rtortosa, "on_key_press_event", rtortosa_on_key_press_event, 2);
  rb_define_module_function(m_rtortosa, "pick_a_color", rtortosa_pick_a_color, 0);
  gtk_window_wrapper(m_rtortosa);
  gtk_notebook_wrapper(m_rtortosa);
  VALUE c_color = generate_color_ruby_class_under(m_rtortosa); 
}
