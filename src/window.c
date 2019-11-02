#include "window.h"
#include "terminal.h"

struct _TortosaWindow {
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE(TortosaWindow, tortosa_window, GTK_TYPE_APPLICATION_WINDOW)

static void
tortosa_window_class_init (TortosaWindowClass *klass)
{

}

static void
tortosa_window_init (TortosaWindow *window)
{
    GtkWidget *headerbar;
    GtkWidget *vte;

    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
    gtk_widget_set_name (GTK_WIDGET (window), "tortosa-window");

    headerbar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
    gtk_widget_set_name (headerbar, "tortosa-headerbar");
    gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);

    vte = tortosa_terminal_new ();
    gtk_container_add (GTK_CONTAINER (window), vte);

}

TortosaWindow *
tortosa_window_new (TortosaApplication *application)
{
    return g_object_new (TORTOSA_WINDOW_TYPE,
                         "application",
                         G_APPLICATION (application),
                         NULL);
}
