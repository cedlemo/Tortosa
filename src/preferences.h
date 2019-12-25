#ifndef TORTOSA_PREFERENCES_H
#define TORTOSA_PREFERENCES_H
#include <gtk/gtk.h>
#include "window.h"

#define TORTOSA_PREFERENCES_TYPE (tortosa_preferences_get_type ())
G_DECLARE_FINAL_TYPE (TortosaPreferences, tortosa_preferences, TORTOSA, PREFERENCES, GtkDialog)
TortosaPreferences *tortosa_preferences_new (TortosaWindow *win);
#endif /* TORTOSA_PREFERENCES_H */
