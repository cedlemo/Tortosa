#include <gtk/gtk.h>
#include "backbone.h"
#include "dbg.h"

#ifndef EVENTS_H
#define EVENTS_H
gboolean event_key_press(GtkWidget *, GdkEventKey *, backbone_t *);
gboolean event_button_press(GtkWidget* , GdkEventButton *, backbone_t * );
#endif
