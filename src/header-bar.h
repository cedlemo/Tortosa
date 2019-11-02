#ifndef TORTOSA_HEADER_BAR_H
#define TORTOSA_HEADER_BAR_H
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define TORTOSA_HEADER_BAR_TYPE (tortosa_header_bar_get_type ())
G_DECLARE_FINAL_TYPE (TortosaHeaderBar, tortosa_header_bar, TORTOSA, HEADER_BAR, GtkHeaderBar)

TortosaHeaderBar * tortosa_header_bar_new (void);
G_END_DECLS

#endif /* TORTOSA_HEADER_BAR_H */
