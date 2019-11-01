#include "application.h"
#include "terminal.h"
#include "shell.h"
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
    printf("Application instance init\n");
}

static void tortosa_startup (GApplication *app);
static void tortosa_activate (GApplication *app);
static int tortosa_command_line (GApplication *application, GApplicationCommandLine *cmdline);

static void
tortosa_application_class_init (TortosaApplicationClass *klass)
{
    printf("Application class init start\n");
    G_APPLICATION_CLASS (klass)->startup = tortosa_startup;
    G_APPLICATION_CLASS (klass)->activate = tortosa_activate;
    G_APPLICATION_CLASS (klass)->command_line = tortosa_command_line;
    printf("Application class init end\n");
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
    GtkWidget *window;
    GtkWidget *headerbar;
    GtkWidget *vte;

    window = gtk_application_window_new (GTK_APPLICATION (app));
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
    gtk_widget_set_name (window, "tortosa-window");

    headerbar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
    gtk_widget_set_name (headerbar, "tortosa-headerbar");
    gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);

    vte = tortosa_terminal_new ();
    gtk_container_add (GTK_CONTAINER (window), vte);
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

  g_application_command_line_print (cmdline,
                                    "This text is written back\n"
                                    "to stdout of the caller\n");

  for (i = 0; i < argc; i++)
    g_print ("argument %d: %s\n", i, argv[i]);

  g_strfreev (argv);

  g_application_activate(application);

  return 0;
}

TortosaApplication *
tortosa_application_new ()
{
    printf("Tortosa application new\n");
    return g_object_new (TORTOSA_APPLICATION_TYPE,
                         "application-id", APP_ID,
                         "flags", G_APPLICATION_NON_UNIQUE | G_APPLICATION_HANDLES_COMMAND_LINE,
                         NULL);
}
