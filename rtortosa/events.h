#ifndef EVENTS_H
#define EVENTS_H
#include <gtk/gtk.h>
#include <ruby.h>
gboolean default_event_key_press(GtkWidget *widget, GdkEventKey *event, void * userdata);
VALUE rtortosa_on_key_press_event(VALUE self, VALUE callback, VALUE userdata);
VALUE rtortosa_on_entry_validate_event(VALUE self, VALUE callback, VALUE userdata);
#endif
