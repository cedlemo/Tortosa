#include <stdlib.h>
#include <vte/vte.h>
#include "gears.h"
#include "backbone.h"
#include "colors.h"
#include "dbg.h"

void free_backbone( backbone_t * backbone)
{
	FREE_GSTRING(backbone->window.background.color);
  FREE_GSTRING(backbone->command.line);	
}

void quit_gracefully(backbone_t * backbone)
{
	free_backbone(backbone);
  gtk_main_quit();
}
void widget_set_transparent_background(GtkWidget *widget)
{
  GdkRGBA transparent;
  transparent.red =0;
  transparent.green = 0;
  transparent.blue = 0;
  transparent.alpha = 0;
  gtk_widget_override_background_color(widget,GTK_STATE_FLAG_NORMAL,&transparent);

}
