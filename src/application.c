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

#include "application.h"
#include "shell.h"
#include "window.h"
#include "stdio.h"

#define APP_ID "com.github.cedlemo.tortosa"
#define APP_NAME "Tortosa"

struct _TortosaApplication {
    GtkApplication parent;
};

G_DEFINE_TYPE(TortosaApplication, tortosa_application, GTK_TYPE_APPLICATION)

static void
tortosa_application_init (TortosaApplication *app)
{
}

static void tortosa_startup (GApplication *app);
static void tortosa_activate (GApplication *app);
static int tortosa_command_line (GApplication *application, GApplicationCommandLine *cmdline);

static void
tortosa_application_class_init (TortosaApplicationClass *klass)
{
    G_APPLICATION_CLASS (klass)->startup = tortosa_startup;
    G_APPLICATION_CLASS (klass)->activate = tortosa_activate;
    G_APPLICATION_CLASS (klass)->command_line = tortosa_command_line;
}

static void
tortosa_application_dispose (GObject *object)
{
    g_debug ("dispose application");
}

static void
tortosa_startup (GApplication *app)
{
    G_APPLICATION_CLASS (tortosa_application_parent_class)->startup (app);
    g_set_application_name (APP_NAME);
    g_set_prgname (APP_NAME);

    GtkCssProvider *cssProvider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(cssProvider, "theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
}

static void
tortosa_activate (GApplication *app)
{
    TortosaWindow *window= tortosa_window_new (TORTOSA_APPLICATION (app));
    tortosa_shell_get_default (); // used just to be sure that the shell is initialized
    tortosa_shell_set_application (app);

    gtk_widget_show_all (GTK_WIDGET (window));
    gtk_window_present (GTK_WINDOW (window));
}

static int
tortosa_command_line (GApplication            *application,
                      GApplicationCommandLine *cmdline)
{
  gchar **argv;
  gint argc;
  gint i;

  argv = g_application_command_line_get_arguments (cmdline, &argc);

  g_message("Launching Tortosa (%s) ..oO | Oo..", argv[0]);

  for (i = 1; i < argc; i++)
    g_message("\targ. %d : %s", i, argv[i]);

  g_strfreev (argv);

  g_application_activate(application);

  return 0;
}

TortosaApplication *
tortosa_application_new ()
{
    return g_object_new (TORTOSA_APPLICATION_TYPE,
                         "application-id", APP_ID,
                         "flags", G_APPLICATION_NON_UNIQUE | G_APPLICATION_HANDLES_COMMAND_LINE,
                         NULL);
}
