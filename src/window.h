#ifndef TORTOSA_WINDOW_H
#define TORTOSA_WINDOW_H
#include <gtk/gtk.h>
#include "application.h"

G_BEGIN_DECLS
#define TORTOSA_WINDOW_TYPE (tortosa_window_get_type ())

G_DECLARE_FINAL_TYPE (TortosaWindow, tortosa_window, TORTOSA, WINDOW, GtkApplicationWindow)

TortosaWindow * tortosa_window_new (TortosaApplication * application);
G_END_DECLS
#endif /* TORTOSA_WINDOW_H*/
