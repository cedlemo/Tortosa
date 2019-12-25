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
#include "preferences.h"
#include "stdio.h"

#define APP_ID "com.github.cedlemo.tortosa"
#define APP_NAME "Tortosa"

struct _TortosaApplication {
    GtkApplication parent_instance;
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
preferences_activated (GSimpleAction *action,
                       GVariant      *parameter,
                       gpointer       app)
{
    TortosaPreferences *prefs;
    GtkWindow *win;

    win = gtk_application_get_active_window (GTK_APPLICATION (app));
    prefs = tortosa_preferences_new (TORTOSA_WINDOW (win));
    gtk_window_present (GTK_WINDOW (prefs));
}

static void
quit_activated (GSimpleAction *action,
                GVariant      *parameter,
                gpointer       app)
{
    g_application_quit (G_APPLICATION (app));
}

static GActionEntry app_entries[] =
{
  { "preferences", preferences_activated, NULL, NULL, NULL },
  { "quit", quit_activated, NULL, NULL, NULL }
};

static void
tortosa_startup (GApplication *app)
{
    GtkBuilder *builder;
    GMenuModel *app_menu;
    const gchar *quit_accels[2] = { "<Ctrl>Q", NULL };


    G_APPLICATION_CLASS (tortosa_application_parent_class)->startup (app);
    g_set_application_name (APP_NAME);
    g_set_prgname (APP_NAME);

    GtkCssProvider *cssProvider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(cssProvider, "theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    g_action_map_add_action_entries (G_ACTION_MAP (app),
            app_entries, G_N_ELEMENTS (app_entries),
            app);
    gtk_application_set_accels_for_action (GTK_APPLICATION (app),
            "app.quit",
            quit_accels);

    builder = gtk_builder_new_from_resource ("/com/github/cedlemo/tortosa/app-menu.ui");
    app_menu = G_MENU_MODEL (gtk_builder_get_object (builder, "appmenu"));
    gtk_application_set_app_menu (GTK_APPLICATION (app), app_menu);
    g_object_unref (builder);
}

static void
tortosa_activate (GApplication *app)
{
    TortosaWindow *window = tortosa_window_new (TORTOSA_APPLICATION (app));

    tortosa_shell_set_application (app);
    tortosa_shell_set_window (window);
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
