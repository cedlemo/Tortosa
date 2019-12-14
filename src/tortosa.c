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

#include <gtk/gtk.h>
#include "application.h"
#include "shell.h"

int main(int argc,
         char **argv)
{
    int status;
    TortosaShell *shell = tortosa_shell_get_default ();

    status = g_application_run (G_APPLICATION (tortosa_application_new ()), argc, argv);

    g_clear_object(&shell);

    return status;
}
