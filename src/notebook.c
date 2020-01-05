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

#include "notebook.h"
#include "shell.h"

struct _TortosaNotebook {
    GtkNotebook parent_instance;
};

G_DEFINE_TYPE (TortosaNotebook, tortosa_notebook, GTK_TYPE_NOTEBOOK)

static void
tortosa_notebook_class_init (TortosaNotebookClass *klass)
{

}

static void
handle_current_page_changed (GtkNotebook *notebook,
                             GtkWidget   *page,
                             guint        page_num,
                             gpointer     user_data)
{
    GtkLabel *term_title = tortosa_shell_get_term_title ();
    VteTerminal *terminal = VTE_TERMINAL (page);
    gtk_label_set_text (term_title, vte_terminal_get_window_title (terminal));
}

static void
tortosa_notebook_init (TortosaNotebook *notebook)
{
    gtk_widget_set_name (GTK_WIDGET (notebook), "tortosa-notebook");
    gtk_notebook_set_show_tabs (GTK_NOTEBOOK (notebook), FALSE);
    gtk_notebook_set_show_border (GTK_NOTEBOOK (notebook), FALSE);

    g_signal_connect (notebook, "switch-page", G_CALLBACK (handle_current_page_changed), NULL);
}

TortosaNotebook *
tortosa_notebook_new (void)
{
    return g_object_new (TORTOSA_NOTEBOOK_TYPE, NULL);
}

int
tortosa_notebook_add_terminal (TortosaNotebook *notebook)
{
    g_debug ("Add new terminal in notebook");
    int current;
    GtkWidget *terminal = GTK_WIDGET (tortosa_terminal_new ());
    gtk_widget_show (terminal);
    current = gtk_notebook_append_page (GTK_NOTEBOOK (notebook),
                                        terminal,
                                        NULL);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook), current);
    return current;
}

int
tortosa_notebook_close_terminal (TortosaNotebook *notebook, TortosaTerminal *terminal)
{
    GList *l = NULL;
    GList *children = gtk_container_get_children (GTK_CONTAINER (notebook));
    int i = 0;

    g_debug ("Looking for the terminal to close");
    for (l = children; l != NULL; l = l->next)
    {
        TortosaTerminal *t = TORTOSA_TERMINAL (l->data);
        if(t == terminal) break;
        i++;
    }

    if(l != NULL) {
        g_debug ("Removing terminal %d", i);
        gtk_notebook_remove_page (GTK_NOTEBOOK (notebook), i);
        if(terminal != NULL) {
            gtk_widget_destroy (GTK_WIDGET (terminal));
        }
    }

    g_list_free (children);

    return gtk_notebook_get_n_pages (GTK_NOTEBOOK (notebook));
}

TortosaTerminal *
tortosa_notebook_get_current_terminal (TortosaNotebook *notebook)
{
    int current = gtk_notebook_get_current_page (GTK_NOTEBOOK (notebook));
    return TORTOSA_TERMINAL (gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook), current));
}

void
tortosa_notebook_next (TortosaNotebook *notebook)
{
    g_debug ("Go to next terminal in notebook");
    GtkNotebook *_noteb = GTK_NOTEBOOK (notebook);
    int current, next, n;
    current = gtk_notebook_get_current_page (_noteb);
    next = current + 1;
    n = gtk_notebook_get_n_pages (_noteb);
    if(next >= n)
        next = 0;
    g_message ("n %d current %d next %d", n, current, next);
    gtk_notebook_set_current_page (_noteb, next);
}

void
tortosa_notebook_prev (TortosaNotebook *notebook)
{
    g_debug ("Go to prev terminal in notebook");
    GtkNotebook *_noteb = GTK_NOTEBOOK (notebook);
    int current, prev, n;
    current = gtk_notebook_get_current_page (_noteb);
    prev = current - 1;
    n = gtk_notebook_get_n_pages (_noteb);
    if(prev < 0)
        prev = n - 1;
    gtk_notebook_set_current_page (_noteb, prev);
}
