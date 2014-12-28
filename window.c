#include <gtk/gtk.h>
#include "window.h"
#include "backbone.h"
#include "gears.h"
#include "dbg.h"

gboolean init_window_visual_with_alpha( GtkWidget * window, backbone_t * backbone )
{
	gtk_widget_set_app_paintable(window, TRUE);
	backbone->screen = gtk_widget_get_screen(window);
	GdkVisual * visual;
	visual = gdk_screen_get_rgba_visual(backbone->screen);
	if ( visual != NULL && gdk_screen_is_composited(backbone->screen))
	{
		gtk_widget_set_visual(window, visual);
		backbone->window.transparency = TRUE;
		return TRUE;
	}
	else
	{
		visual = gdk_screen_get_system_visual (backbone->screen);
		gtk_widget_set_visual (GTK_WIDGET (window), visual);
		backbone->window.transparency = FALSE;
		return FALSE;
	}
}

gboolean draw_window_background(GtkWidget *widget, cairo_t *cr, backbone_t * backbone)
{      
	if(widget == backbone->window.widget)
	{
		
		if (backbone->window.transparency)
		{  
			cairo_set_source_rgba (cr,	backbone->window.background.rgba.red, 
																	backbone->window.background.rgba.green, 
																	backbone->window.background.rgba.blue, 
																	backbone->window.background.rgba.alpha); 
		}
		else
		{	    
			cairo_set_source_rgb (cr, backbone->window.background.rgba.red, backbone->window.background.rgba.green, backbone->window.background.rgba.blue); 
		}
		cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
		cairo_paint(cr);
		cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
		//pango_cairo_show_layout (cr, backbone->window.layout);
    return FALSE;
	}
  return FALSE;
/*Must always return false otherwise tabs are not displayed don't know why*/
}

