#ifndef EVENTS_H
#define EVENTS_H
#include <gtk/gtk.h>
#include "backbone.h"
#include "dbg.h"
gboolean event_key_press(GtkWidget *, GdkEventKey *, backbone_t *);
gboolean event_button_press(GtkWidget* , GdkEventButton *, backbone_t * );
gboolean get_window_state(GtkWidget*, GdkEventWindowState *, backbone_t *);
#endif
