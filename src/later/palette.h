#ifndef TORTOSA_PALETTE_H
#define TORTOSA_PALETTE_H
include <glib-object.h>

G_BEGIN_DECLS

/*
 * Type declaration.
 */
#define TORTOSA_TYPE_PALETTE tortosa_palette_get_type ()
G_DECLARE_FINAL_TYPE (TortosaPalette, tortosa_palette, TORTOSA, PALETTE, GObject)

/*
 * Method definitions.
 */
TortosaPalette *tortosa_palette_new (void);

G_END_DECLS
#endif
