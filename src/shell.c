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

#include "shell.h"

struct _TortosaShell {
    GObject parent_instance;
};

static TortosaShell * tortosa_shell = NULL;

G_DEFINE_TYPE (TortosaShell, tortosa_shell, G_TYPE_OBJECT)

static void
tortosa_shell_dispose (GObject *gobject)
{
    G_OBJECT_CLASS (tortosa_shell_parent_class)->dispose (gobject);
}

static void
tortosa_shell_finalize (GObject *gobject)
{
    G_OBJECT_CLASS (tortosa_shell_parent_class)->finalize (gobject);
}

/**
 * Tortosa shell Class init (called only once)
 * */
static void
tortosa_shell_class_init (TortosaShellClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);
    object_class->finalize = tortosa_shell_finalize;
    object_class->dispose = tortosa_shell_dispose;
}

/**
 * Tortosa shell Instance init (called each time g_object_new is
 * called with TORTOSA_TYPE_SHELL)
 * */
static void
tortosa_shell_init (TortosaShell *self)
{
}

static TortosaShell *
tortosa_shell_new ()
{
    return g_object_new (TORTOSA_SHELL_TYPE, NULL);
}

TortosaShell *
tortosa_shell_get_default ()
{
    if (tortosa_shell == NULL)
        tortosa_shell = tortosa_shell_new ();

    return tortosa_shell;
}
