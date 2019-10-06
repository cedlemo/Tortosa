#include "application.h"

#define APP_ID "com.github.cedlemo.tortosa"

static void
activate (GtkApplication *app,
          gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *headerbar;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

    headerbar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);
    gtk_widget_show_all (window);
}

static int
command_line (GApplication            *application,
              GApplicationCommandLine *cmdline)
{
  gchar **argv;
  gint argc;
  gint i;

  argv = g_application_command_line_get_arguments (cmdline, &argc);

  g_application_command_line_print (cmdline,
                                    "This text is written back\n"
                                    "to stdout of the caller\n");

  for (i = 0; i < argc; i++)
    g_print ("argument %d: %s\n", i, argv[i]);

  g_strfreev (argv);

  g_application_activate(application);

  return 0;
}

GtkApplication *
tortosa_application_new ()
{
    GtkApplication *app;

    app = gtk_application_new (APP_ID, G_APPLICATION_NON_UNIQUE | G_APPLICATION_HANDLES_COMMAND_LINE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    g_signal_connect (app, "command-line", G_CALLBACK (command_line), NULL);

    return app;
}
