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

#include "header-bar.h"

struct _TortosaHeaderBar {
    GtkHeaderBar parent_instance;
};

G_DEFINE_TYPE (TortosaHeaderBar, tortosa_header_bar, GTK_TYPE_HEADER_BAR)

static void
tortosa_header_bar_init (TortosaHeaderBar *header_bar)
{
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_widget_set_name (GTK_WIDGET (header_bar), "tortosa-headerbar");
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
