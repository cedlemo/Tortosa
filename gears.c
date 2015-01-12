#include <stdlib.h>
#include <vte/vte.h>
#include "gears.h"
#include "backbone.h"
#include "colors.h"
#include "dbg.h"
#include "gtk_vte_methods.h"
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

gint find_node_by_widget( gconstpointer node, gconstpointer widget)
{
  if( ((vte_t *) node)->widget == (GtkWidget *)widget)
    return 0;
  else
    return 1;
}

void remove_node_by_widget( GSList *slist, GtkWidget *widget)
{
  /*find the node for the widget*/
  GSList *found = NULL;
  found = g_slist_find_custom(slist, widget, (GCompareFunc) find_node_by_widget);
  /*remove it and free the data*/
  if (found)
  {
    /*release memory for tab_data slist*/
    slist = g_slist_delete_link(slist, found); 
  }
  else
    LOG_WARN("data for tab not found....\n");
}
