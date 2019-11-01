#include <gtk/gtk.h>
#include "application.h"

int main(int argc,
         char **argv)
{
    GtkApplication *app;

    return g_application_run (G_APPLICATION (tortosa_application_new ()), argc, argv);
}
