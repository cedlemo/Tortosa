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

#ifndef TORTOSA_EVENT_LABEL_H
#define TORTOSA_EVENT_LABEL_H
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define TORTOSA_EVENT_LABEL_TYPE (tortosa_event_label_get_type ())
G_DECLARE_FINAL_TYPE (TortosaEventLabel, tortosa_event_label, TORTOSA, EVENT_LABEL, GtkEventBox)

typedef gboolean (*BUTTON_PRESS_CB)(GtkWidget *event_box, GdkEvent *event, gpointer data);

TortosaEventLabel * tortosa_event_label_new (gchar *label);
void                tortosa_event_label_set_button_press_cb (TortosaEventLabel *event_label,
                                                             BUTTON_PRESS_CB cb);

G_END_DECLS

#endif /* TORTOSA_EVENT_LABEL_H */
