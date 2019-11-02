#include "header-bar.h"

struct _TortosaHeaderBar {
    GtkHeaderBar parent;
};

G_DEFINE_TYPE (TortosaHeaderBar, tortosa_header_bar, GTK_TYPE_HEADER_BAR)

static void
tortosa_header_bar_init (TortosaHeaderBar *header_bar)
{
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_widget_set_name (GTK_WIDGET (header_bar), "tortosa-headerbar");
}

static void
tortosa_header_bar_class_init (TortosaHeaderBarClass *klass)
{

}

TortosaHeaderBar *
tortosa_header_bar_new (void)
{
    return g_object_new (TORTOSA_HEADER_BAR_TYPE, NULL);
}
