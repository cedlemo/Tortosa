#include <stdlib.h>
#include <gtk/gtk.h>
#include "colors.h"
#include "dbg.h"

/*Stuff in order to replace gdk_color_parse*/
#include "pango-color-table.h"

#define ISUPPER(c)              ((c) >= 'A' && (c) <= 'Z')
#define TOLOWER(c)              (ISUPPER (c) ? (c) - 'A' + 'a' : (c))

static int compare_xcolor_entries (const void *a, const void *b)
{
  const guchar *s1 = (const guchar *) a;
  const guchar *s2 = (const guchar *) (color_names + ((const ColorEntry *) b)->name_offset);

  while (*s1 && *s2)
    {
      int c1, c2;
      while (*s1 == ' ') s1++;
      while (*s2 == ' ') s1++;
      c1 = (gint)(guchar) TOLOWER (*s1);
      c2 = (gint)(guchar) TOLOWER (*s2);
      if (c1 != c2)
        return (c1 - c2);
      s1++; s2++;
    }

  return ((gint) *s1) - ((gint) *s2);
}

static gboolean find_gdkRGBA_color(const char *name, GdkRGBA *color)
{
  ColorEntry *found;

  found = bsearch (name, color_entries, G_N_ELEMENTS (color_entries),
		   sizeof (ColorEntry),
		   compare_xcolor_entries);
  if (found == NULL)
    return FALSE;

  if (color)
    {
      color->red = found->red  / 255;
      color->green = found->green  / 255;
      color->blue = found->blue  / 255;
			color->alpha = 1;
    }

  return TRUE;
}

static gboolean hex (const char *spec, int len, unsigned int *c)
{
  const char *end;
  *c = 0;
  for (end = spec + len; spec != end; spec++)
    if (g_ascii_isxdigit (*spec))
      *c = (*c << 4) | g_ascii_xdigit_value (*spec);
    else
      return FALSE;
  return TRUE;
}

static gboolean hex_rgba_color_parse (GdkRGBA *color,  const char *spec)
{
  g_return_val_if_fail (spec != NULL, FALSE);
	/*hex value of the color*/
  if (spec[0] == '#')
    {
      size_t len;
      unsigned int r, g, b;

      spec++;
      len = strlen (spec);
			/*rgb*/
			if (len % 3 == 0 && len >= 3 && len <= 12)
      {
				len /= 3;

				if (!hex (spec, len, &r) || !hex (spec + len, len, &g) ||  !hex (spec + len * 2, len, &b))
					return FALSE;

				if (color)
				{
					int bits = len * 4;
					r <<= 16 - bits;
					g <<= 16 - bits;
					b <<= 16 - bits;
					while (bits < 16)
					{
						r |= (r >> bits);
						g |= (g >> bits);
						b |= (b >> bits);
						bits *= 2;
					}
					color->red   = r/65535.;
					color->green = g/65535.;
					color->blue  = b/65535.;
					color->alpha = 1;
				}
			}
			/*rgba*/
			else if (len % 4 == 0 && len >= 4 && len <= 16)
			{
				unsigned int a;
				len /= 4;

				if (!hex (spec, len, &r) || !hex (spec + len, len, &g) ||  !hex (spec + len * 2, len, &b) ||  !hex (spec + len * 3, len, &a))
					return FALSE;

				if (color)
				{
					int bits = len * 4;
					r <<= 16 - bits;
					g <<= 16 - bits;
					b <<= 16 - bits;
					a <<= 16 - bits;
					while (bits < 16)
					{
						r |= (r >> bits);
						g |= (g >> bits);
						b |= (b >> bits);
						a |= (a >> bits);
						bits *= 2;
					}
					color->red   = r/65535.;
					color->green = g/65535.;
					color->blue  = b/65535.;
					color->alpha = a/65535.;
				}
			}
    }
	/*x11 color string*/
  else
    {
				SENTINEL("enter X11 color search");
      if (!find_gdkRGBA_color (spec, color))
	return FALSE;
    }
  return TRUE;
}

#define SKIP_WHITESPACES(s) while (*(s) == ' ') (s)++;

static gboolean
parse_rgb_value (const gchar *str, gchar **endp, gdouble *number)
{
  const char *p;

  *number = g_ascii_strtod (str, endp);
  if (errno == ERANGE || *endp == str ||
      isinf (*number) || isnan (*number))
    return FALSE;

  p = *endp;

  SKIP_WHITESPACES (p);

  if (*p == '%')
    {
      *endp = (char *)(p + 1);
      *number = CLAMP(*number / 100., 0., 1.);
    }
  else
    {
      *number = CLAMP(*number / 255., 0., 1.);
    }

  return TRUE;
}

gboolean extended_gdk_rgba_parse (GdkRGBA *rgba,  const gchar *spec)
{
	gboolean has_alpha;
  gdouble r, g, b, a;
  gchar *str = (gchar *) spec;
  gchar *p;

  /*str start with rgba*/
	if (strncmp (str, "rgba", 4) == 0)
    {
      has_alpha = TRUE;
      str += 4;
    }
  /*str start with rgb*/
  else if (strncmp (str, "rgb", 3) == 0)
    {
      has_alpha = FALSE;
      a = 1;
      str += 3;
    }
  /* parse rgb.txt color  map and '#' prefixed colors */
	else
    {
			GdkRGBA color;
       if (hex_rgba_color_parse (&color, str))
        {
          if (rgba)
            {
              rgba->red = color.red;
              rgba->green = color.green;
              rgba->blue = color.blue;
              rgba->alpha = color.alpha;
            }

          return TRUE;
        }
      else
        return FALSE;
    }

  SKIP_WHITESPACES (str);

  if (*str != '(')
    return FALSE;

  str++;

  /* Parse red */
  SKIP_WHITESPACES (str);
  if (!parse_rgb_value (str, &str, &r))
    return FALSE;
  SKIP_WHITESPACES (str);

  if (*str != ',')
    return FALSE;

  str++;

  /* Parse green */
  SKIP_WHITESPACES (str);
  if (!parse_rgb_value (str, &str, &g))
    return FALSE;
  SKIP_WHITESPACES (str);

  if (*str != ',')
    return FALSE;

  str++;

  /* Parse blue */
  SKIP_WHITESPACES (str);
  if (!parse_rgb_value (str, &str, &b))
    return FALSE;
  SKIP_WHITESPACES (str);

  if (has_alpha)
    {
      if (*str != ',')
        return FALSE;

      str++;

      SKIP_WHITESPACES (str);
      a = g_ascii_strtod (str, &p);
      if (errno == ERANGE || p == str ||
          isinf (a) || isnan (a))
        return FALSE;
      str = p;
      SKIP_WHITESPACES (str);
    }

  if (*str != ')')
    return FALSE;

  str++;

  SKIP_WHITESPACES (str);

  if (*str != '\0')
    return FALSE;

  if (rgba)
    {
      rgba->red = CLAMP (r, 0, 1);
      rgba->green = CLAMP (g, 0, 1);
      rgba->blue = CLAMP (b, 0, 1);
      rgba->alpha = CLAMP (a, 0, 1);
	}

	return TRUE;
}
#undef SKIP_WHITESPACES
