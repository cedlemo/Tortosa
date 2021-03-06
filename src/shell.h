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

#ifndef TORTOSA_SHELL_H
#define TORTOSA_SHELL_H
#include <glib-object.h>
#include "notebook.h"
#include "window.h"
#include "application.h"

G_BEGIN_DECLS

#define TORTOSA_SHELL_TYPE tortosa_shell_get_type ()
G_DECLARE_FINAL_TYPE( TortosaShell, tortosa_shell, TORTOSA, SHELL, GObject)

TortosaShell         *tortosa_shell_get_default (void);
void                 tortosa_shell_set_notebook (TortosaNotebook *notebook);
TortosaNotebook      *tortosa_shell_get_notebook (void);
void                 tortosa_shell_set_application (GApplication *application);
GApplication         *tortosa_shell_get_application (void);
void                 tortosa_shell_set_window (TortosaWindow *window);
TortosaWindow        *tortosa_shell_get_window (void);
GSettings            *tortosa_shell_get_settings (void);
void                 tortosa_shell_set_termmenu (GtkPopover *popover);
GtkPopover           *tortosa_shell_get_termmenu (void);
GtkLabel             *tortosa_shell_get_term_title (void);
G_END_DECLS
#endif /* !TORTOSA_SHELL_H */
