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

#ifndef TORTOSA_WINDOW_H
#define TORTOSA_WINDOW_H
#include <gtk/gtk.h>
#include "application.h"

G_BEGIN_DECLS
#define TORTOSA_WINDOW_TYPE (tortosa_window_get_type ())

G_DECLARE_FINAL_TYPE (TortosaWindow, tortosa_window, TORTOSA, WINDOW, GtkApplicationWindow)

TortosaWindow * tortosa_window_new (TortosaApplication * application);
G_END_DECLS
#endif /* TORTOSA_WINDOW_H*/
