#include "events.h"
//#include "terminal.h"
#include "gtk_vte_methods.h"
#include "tabs.h"
#include "backbone.h"

gboolean default_event_key_press(GtkWidget *widget, GdkEventKey *event, void * userdata)
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
    if (g == GDK_KEY_T) {
      VALUE m_rtortosa = rb_const_get( rb_cObject, rb_intern( "Rtortosa" ) );
      VALUE cVte = rb_const_get_at( m_rtortosa, rb_intern("Vte"));
      VALUE params[1];
      params[0] = Qnil;
      VALUE vte = rb_class_new_instance(1, params, cVte);
      return TRUE;
    }
    if (g == GDK_KEY_Left) {
      go_to_prev_tab(GTK_NOTEBOOK(backbone.window.notebook));
      return TRUE;
    }
    if (g == GDK_KEY_Right) {
      go_to_next_tab(GTK_NOTEBOOK(backbone.window.notebook));
      return TRUE;
    }
  }
  else 
  {
    if(g == GDK_KEY_Escape && backbone.command.mode){
      gtk_widget_hide(backbone.window.entry);
      gtk_widget_grab_focus(notebook_get_current_widget(GTK_NOTEBOOK(backbone.window.notebook)));
      backbone.command.mode = FALSE;
      return TRUE;
    }
  }
  return FALSE;
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
  VALUE self;
  callback = rb_ary_entry(passthrough, 0);
  self = rb_ary_entry(passthrough, 1);
  callback_data = rb_ary_entry(passthrough, 2);
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
    if (g == GDK_KEY_Left) {
      go_to_prev_tab(GTK_NOTEBOOK(backbone.window.notebook));
      return TRUE;
    }
    if (g == GDK_KEY_Right) {
      go_to_next_tab(GTK_NOTEBOOK(backbone.window.notebook));
      return TRUE;
    }
  }
  else 
  {
    if(g == GDK_KEY_Escape && backbone.command.mode){
      gtk_widget_hide(backbone.window.entry);
      gtk_widget_grab_focus(notebook_get_current_widget(GTK_NOTEBOOK(backbone.window.notebook)));
      backbone.command.mode = FALSE;
      return TRUE;
    }
  }
  rb_funcall(callback, rb_intern("call"), 3, self, e, callback_data);
  return FALSE;
}
VALUE rtortosa_on_key_press_event(VALUE self, VALUE callback, VALUE userdata)
{
  g_signal_handler_disconnect(backbone.window.widget,
                              backbone.window.key_event_handler_id);
  VALUE passthrough;
  
  if((callback != Qnil) && (rb_class_of(callback) != rb_cProc))
    rb_raise(rb_eTypeError, "Expected Proc callback");

  passthrough = rb_ary_new();
  rb_ary_store(passthrough, 0, callback);
  rb_ary_store(passthrough, 1, self);  
  rb_ary_store(passthrough, 2, userdata);  
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
  VALUE self;
  callback = rb_ary_entry(passthrough, 0);
  self = rb_ary_entry(passthrough, 1);
  callback_data = rb_ary_entry(passthrough, 2);
  VALUE command_line = rb_str_new2(gtk_entry_get_text(GTK_ENTRY(backbone.window.entry)));
  rb_funcall(callback, rb_intern("call"), 3, self, command_line, callback_data); 

}
VALUE rtortosa_on_entry_validate_event(VALUE self, VALUE callback, VALUE userdata)
{
  VALUE passthrough;
/*pass self in the first agument so that the user can call win::*/  
  if(rb_class_of(callback) != rb_cProc)
    rb_raise(rb_eTypeError, "Expected Proc callback");

  passthrough = rb_ary_new();
  rb_ary_store(passthrough, 0, callback);
  rb_ary_store(passthrough, 1, self);  
  rb_ary_store(passthrough, 2, userdata);  
  g_signal_connect( backbone.window.entry, 
                    "activate", 
                    G_CALLBACK(parse_command_line),
                    (void *) passthrough);
  return Qnil;
}
