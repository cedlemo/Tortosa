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
#include <stdio.h>

G_BEGIN_DECLS

#define TORTOSA_SHELL_TYPE tortosa_shell_get_type ()
G_DECLARE_FINAL_TYPE( TortosaShell, tortosa_shell, TORTOSA, SHELL, GObject)

TortosaShell *tortosa_shell_get_default (void);
G_END_DECLS
#endif /* !TORTOSA_SHELL_H */
