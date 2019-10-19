#include "palette.h"

enum
{
  BACKGROUND = 1,
  FOREGROUND,
  COLOR0,
  COLOR1,
  COLOR2,
  COLOR3,
  COLOR4,
  COLOR5,
  COLOR6,
  COLOR7,
  COLOR8,
  COLOR9,
  COLOR10,
  COLOR11,
  COLOR12,
  COLOR15,
  COLOR16,
  N_PROPERTIES
};
// Create properties with this.
struct _TortosaPalette
{
  GObject parent_instance;

  /* Other members, including private data. */
};

G_DEFINE_TYPE (TortosaPalette, tortosa_palette, G_TYPE_OBJECT)

static void
tortosa_palette_class_init (TortosaPaletteClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->constructed = tortosa_palette_constructed;
}

static void
tortosa_palette_init (TortosaPalette *self)
{
  /* initialize the object */
}
