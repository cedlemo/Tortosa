#include <ruby.h>
#include <gtk/gtk.h>
#include "gears.h"
#include "window.h"
#include "colors.h"
#include "backbone.h"
#include "stdio.h"
#include "gtk_window_methods.h"
#include "gtk_notebook_methods.h"
#include "gtk_vte_methods.h"
#include "events.h"
#include "fonts.h"
backbone_t backbone;

static  VALUE rtortosa_initialize( VALUE self, VALUE args)
{
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
  widget_set_transparent_background(backbone.window.vbox);
  gtk_container_add(GTK_CONTAINER(backbone.window.widget), backbone.window.vbox);
  /**************/
  /*GtkNotebook */
  /**************/
  backbone.window.notebook = gtk_notebook_new(); 
  widget_set_transparent_background(backbone.window.notebook);
  gtk_box_pack_start(GTK_BOX(backbone.window.vbox), backbone.window.notebook, TRUE, TRUE, 0);

  /***********/
  /* GtkEntry*/
  /***********/
  backbone.window.entry = gtk_entry_new();
  gtk_entry_set_has_frame(GTK_ENTRY(backbone.window.entry),FALSE);
  widget_set_transparent_background(backbone.window.entry);
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
    params[0] = rb_str_new2("#000000");
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
static VALUE rtortosa_pick_a_font(VALUE self)
{
  VALUE font = Qnil;
  GtkResponseType result;
  GtkWidget *dialog = gtk_font_chooser_dialog_new("Pick a font", GTK_WINDOW(backbone.window.widget));
  result = gtk_dialog_run(GTK_DIALOG(dialog));
  if(result == GTK_RESPONSE_OK || result == GTK_RESPONSE_APPLY)
  {
    font_t *f;
    VALUE m_rtortosa = rb_const_get( rb_cObject, rb_intern( "Rtortosa" ) );
    VALUE cFont = rb_const_get_at( m_rtortosa, rb_intern("Font") );
    VALUE params[1];
    params[0] = rb_str_new2(gtk_font_chooser_get_font(GTK_FONT_CHOOSER(dialog)));
    font = rb_class_new_instance( 1, params, cFont );  
  }
  gtk_widget_destroy(dialog);
  return font;
}
static VALUE rtortosa_new_tab(VALUE self, VALUE command)
{
  if(command != Qnil && (TYPE(command) != T_STRING))
    rb_raise(rb_eTypeError, "Expected a string");
  VALUE m_rtortosa = rb_const_get( rb_cObject, rb_intern( "Rtortosa" ) );
  VALUE cVte = rb_const_get_at( m_rtortosa, rb_intern("Vte"));
  VALUE params[1];
  params[0] = command;
  VALUE vte = rb_class_new_instance(1, params, cVte);
  return vte;  
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
  rb_define_module_function(m_rtortosa, "pick_a_font", rtortosa_pick_a_font, 0);
  rb_define_module_function(m_rtortosa, "new_tab", rtortosa_new_tab, 1);
  gtk_window_wrapper(m_rtortosa);
  gtk_notebook_wrapper(m_rtortosa);
  VALUE c_color = generate_color_ruby_class_under(m_rtortosa); 
  VALUE f_font = generate_font_ruby_class_under(m_rtortosa);
  VALUE c_vte = generate_vte_ruby_class_under(m_rtortosa);
}
