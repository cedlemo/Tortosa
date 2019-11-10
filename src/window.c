/*
 * Copyright 2019 Cedric LE MOIGNE, cedlemo@gmx.com
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

#include "window.h"
#include "terminal.h"
#include "header-bar.h"
#include "notebook.h"

struct _TortosaWindow {
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE(TortosaWindow, tortosa_window, GTK_TYPE_APPLICATION_WINDOW)

static void
tortosa_window_class_init (TortosaWindowClass *klass)
{

}

static void
tortosa_window_init (TortosaWindow *window)
{
    TortosaNotebook *notebook;

    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
    gtk_widget_set_name (GTK_WIDGET (window), "tortosa-window");

    gtk_window_set_titlebar(GTK_WINDOW(window), GTK_WIDGET (tortosa_header_bar_new ()));
    notebook = tortosa_notebook_new ();
    tortosa_notebook_add_terminal (notebook);

    gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET (notebook));

    // TODO: Why this unref on floating reference drop notebook
    // g_object_unref (notebook);
}

TortosaWindow *
tortosa_window_new (TortosaApplication *application)
{
    return g_object_new (TORTOSA_WINDOW_TYPE,
                         "application",
                         G_APPLICATION (application),
                         NULL);
}
