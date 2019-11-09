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
tortosa_startup (GApplication *app)
{
    G_APPLICATION_CLASS (tortosa_application_parent_class)->startup (app);
    TortosaShell *tortosa_shell = tortosa_shell_get_default ();
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
    TortosaWindow *window;
    window = tortosa_window_new (TORTOSA_APPLICATION (app));
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
