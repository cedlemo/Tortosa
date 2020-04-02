/*
 * Copyright 2020 Cedric LE MOIGNE, cedlemo@gmx.com
 * This file is part of Tortosa Terminal Emulator.
 *
 * Tortosa is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Tortosa is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tortosa.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "event-label.h"
#include "shell.h"

struct _TortosaEventLabel {
    GtkEventBox parent_instance;
    BUTTON_PRESS_CB button_press_cb;
};

G_DEFINE_TYPE (TortosaEventLabel, tortosa_event_label, GTK_TYPE_EVENT_BOX)

static gboolean
handle_button_press_event (GtkWidget *event_label,
                           GdkEvent  *event,
                           gpointer data)
{
    BUTTON_PRESS_CB cb = (TORTOSA_EVENT_LABEL (event_label))->button_press_cb;

    if (cb != NULL && event->type == GDK_BUTTON_PRESS) {


        GdkEventButton *event_button = (GdkEventButton *) event;
        if(event_button->button == GDK_BUTTON_SECONDARY)
        {
            return TRUE;
        }
        if(event_button->button == GDK_BUTTON_PRIMARY)
        {
            cb(event_label, event, data);
            return TRUE;
        }
    }

    return FALSE;
}


static void
tortosa_event_label_init (TortosaEventLabel *event_label)
{
    event_label->button_press_cb = NULL;
    g_signal_connect (event_label, "button-press-event", G_CALLBACK (handle_button_press_event), NULL);
}

static void
tortosa_event_label_class_init (TortosaEventLabelClass *klass)
{

}

TortosaEventLabel *
tortosa_event_label_new (gchar *label)
{
    TortosaEventLabel * event_label = g_object_new (TORTOSA_EVENT_LABEL_TYPE, NULL);
    gtk_container_add (GTK_CONTAINER (event_label), GTK_WIDGET (gtk_label_new (label)));

    return event_label;
}

void
tortosa_event_label_set_button_press_cb (TortosaEventLabel *event_label, BUTTON_PRESS_CB cb)
{
    event_label->button_press_cb = cb;
}
