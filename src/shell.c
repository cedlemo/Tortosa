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

#include "shell.h"

struct _TortosaShell {
    GObject parent_instance;

    TortosaNotebook *notebook;
    TortosaWindow *window;
    GApplication *application;
    GSettings *settings;
    GtkPopover *termmenu;
    GtkLabel *term_title;
};

static TortosaShell * tortosa_shell = NULL;

G_DEFINE_TYPE (TortosaShell, tortosa_shell, G_TYPE_OBJECT)

static void
tortosa_shell_dispose (GObject *gobject)
{
    G_OBJECT_CLASS (tortosa_shell_parent_class)->dispose (gobject);
    TortosaShell *shell = TORTOSA_SHELL (gobject);
    g_clear_object (&shell->settings);
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
    self->notebook = NULL;
    self->application = NULL;
    self->window = NULL;
    self->settings = g_settings_new ("com.github.cedlemo.tortosa");
    self->termmenu = NULL;
    self->term_title = NULL;
}

static TortosaShell *
tortosa_shell_new (void)
{
    return g_object_new (TORTOSA_SHELL_TYPE, NULL);
}

TortosaShell *
tortosa_shell_get_default (void)
{
    if (tortosa_shell == NULL)
        tortosa_shell = tortosa_shell_new ();

    return tortosa_shell;
}

void
tortosa_shell_set_notebook (TortosaNotebook *notebook) {
    TortosaShell *shell = tortosa_shell_get_default ();
    g_object_ref (notebook);
    shell->notebook = notebook;

}

TortosaNotebook *
tortosa_shell_get_notebook (void)
{
    TortosaShell *shell = tortosa_shell_get_default ();
    return shell->notebook;
}

void
tortosa_shell_set_application (GApplication *application)
{
    TortosaShell *shell = tortosa_shell_get_default ();
    g_object_ref (application);
    shell->application = application;
}

GApplication *
tortosa_shell_get_application (void)
{
    TortosaShell *shell = tortosa_shell_get_default ();
    return shell->application;
}

void
tortosa_shell_set_window (TortosaWindow *window)
{
    TortosaShell *shell = tortosa_shell_get_default ();
    g_object_ref (window);
    shell->window = window;
}

TortosaWindow *
tortosa_shell_get_window (void)
{
    TortosaShell *shell = tortosa_shell_get_default ();
    return shell->window;
}

GSettings *
tortosa_shell_get_settings (void)
{
    TortosaShell *shell = tortosa_shell_get_default ();
    return shell->settings;
}

void
tortosa_shell_set_termmenu (GtkPopover *popover)
{
    TortosaShell *shell = tortosa_shell_get_default ();
    g_object_ref (popover);
    shell->termmenu = popover;
}

GtkPopover *
tortosa_shell_get_termmenu (void)
{
    TortosaShell *shell = tortosa_shell_get_default ();
    return shell->termmenu;
}

GtkLabel *
tortosa_shell_get_term_title (void)
{
    TortosaShell *shell = tortosa_shell_get_default ();
    if(shell->term_title == NULL)
    {
       shell->term_title = GTK_LABEL (gtk_label_new(""));
    }
    return shell->term_title;
}
