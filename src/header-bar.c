/*
 * Copyright 2019-2020 Cedric LE MOIGNE, cedlemo@gmx.com
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

#include "header-bar.h"
#include "event-label.h"
#include "shell.h"
#include "notebook.h"

struct _TortosaHeaderBar {
    GtkHeaderBar parent_instance;
};

G_DEFINE_TYPE (TortosaHeaderBar, tortosa_header_bar, GTK_TYPE_HEADER_BAR)

static gboolean
click_prev (GtkWidget *event_label, GdkEvent *event, gpointer data)
{
    GList *children = gtk_container_get_children (GTK_CONTAINER (event_label));
    GtkLabel *label = GTK_LABEL ((g_list_first (children)->data));
    g_list_free (children);

    g_message ("hit %s", gtk_label_get_text (label));
    TortosaNotebook *notebook = tortosa_shell_get_notebook ();
    tortosa_notebook_prev (notebook);

    return TRUE;
}

static gboolean
click_next (GtkWidget *event_label, GdkEvent *event, gpointer data)
{
    GList *children = gtk_container_get_children (GTK_CONTAINER (event_label));
    GtkLabel *label = GTK_LABEL ((g_list_first (children)->data));
    g_list_free (children);

    g_message ("hit %s", gtk_label_get_text (label));

    TortosaNotebook *notebook = tortosa_shell_get_notebook ();
    tortosa_notebook_prev (notebook);

    return TRUE;
}

static void
tortosa_header_bar_init (TortosaHeaderBar *header_bar)
{
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_widget_set_name (GTK_WIDGET (header_bar), "tortosa-headerbar");

    TortosaEventLabel *prev_label = tortosa_event_label_new ("<");
    tortosa_event_label_set_button_press_cb (prev_label, click_prev);
    TortosaEventLabel *next_label = tortosa_event_label_new (">");
    tortosa_event_label_set_button_press_cb (next_label, click_next);

    gtk_header_bar_pack_start (GTK_HEADER_BAR (header_bar), GTK_WIDGET (prev_label));
    gtk_header_bar_pack_start (GTK_HEADER_BAR (header_bar), GTK_WIDGET (tortosa_shell_get_term_title ()));
    gtk_header_bar_pack_start (GTK_HEADER_BAR (header_bar), GTK_WIDGET (next_label));
}

static void
tortosa_header_bar_class_init (TortosaHeaderBarClass *klass)
{

}

TortosaHeaderBar *
tortosa_header_bar_new (void)
{
    return g_object_new (TORTOSA_HEADER_BAR_TYPE, NULL);
}
