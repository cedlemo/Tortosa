#ifndef TORTOSA_APPLICATION_H
#define TORTOSA_APPLICATION_H
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define TORTOSA_APPLICATION_TYPE (tortosa_application_get_type ())
G_DECLARE_FINAL_TYPE (TortosaApplication, tortosa_application, TORTOSA, APPLICATION, GtkApplication)

TortosaApplication *tortosa_application_new (void);
G_END_DECLS

#endif /* !TORTOSA_APPLICATION_H */
