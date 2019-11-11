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

#include "notebook.h"

struct _TortosaNotebook {
    GtkNotebook parent;
};

G_DEFINE_TYPE (TortosaNotebook, tortosa_notebook, GTK_TYPE_NOTEBOOK)

static void
tortosa_notebook_class_init (TortosaNotebookClass *klass)
{

}

static void
tortosa_notebook_init (TortosaNotebook *notebook)
{
    gtk_widget_set_name (GTK_WIDGET (notebook), "tortosa-notebook");
    gtk_notebook_set_show_tabs (GTK_NOTEBOOK (notebook), FALSE);
    gtk_notebook_set_show_border (GTK_NOTEBOOK (notebook), FALSE);
}

static void
tortosa_notebook_dispose (GObject *object)
{
    g_debug ("notebook dispose");
}

TortosaNotebook *
tortosa_notebook_new (void)
{
    return g_object_new (TORTOSA_NOTEBOOK_TYPE, NULL);
}

int
tortosa_notebook_add_terminal (TortosaNotebook *notebook)
{
    return gtk_notebook_append_page (GTK_NOTEBOOK (notebook),
                                     GTK_WIDGET (tortosa_terminal_new ()),
                                     NULL);
}

int
tortosa_notebook_close_terminal (TortosaNotebook *notebook, VteTerminal *terminal)
{
    GList *l = NULL;
    GList *children = gtk_container_get_children (GTK_CONTAINER (notebook));
    int i = 0;

    for (l = children; l != NULL; l = l->next)
    {
        VteTerminal *t = VTE_TERMINAL (l->data);
        if(t == terminal) break;
        i++;
    }

    if(l != NULL) {
        gtk_notebook_remove_page (GTK_NOTEBOOK (notebook), i);
        g_clear_object (&terminal);
    }

    g_list_free (children);

    return gtk_notebook_get_n_pages (GTK_NOTEBOOK (notebook));
}
