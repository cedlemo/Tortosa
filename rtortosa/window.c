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
/*
gboolean get_window_state(GtkWidget * widget, GdkEventWindowState *event, backbone_t * backbone)
{
	if ( event->new_window_state &GDK_WINDOW_STATE_WITHDRAWN)
	{
		backbone->state.withdrawn = TRUE;
		//SENTINEL("withdraw\n");
	}
	else
		backbone->state.withdrawn = FALSE;
	
	if ( event->new_window_state &GDK_WINDOW_STATE_ICONIFIED)
	{
		backbone->state.iconified = TRUE;
		//SENTINEL("iconified\n");
	}
	else
		backbone->state.iconified = FALSE;
	
	if ( event->new_window_state &GDK_WINDOW_STATE_MAXIMIZED)
	{
		backbone->state.maximized = TRUE;
		//SENTINEL("maximized\n");
	}
	else
		backbone->state.maximized = FALSE;
	
	if ( event->new_window_state &GDK_WINDOW_STATE_STICKY)
	{
		backbone->state.sticky = TRUE;
		//SENTINEL("sticky\n");
	}
	else
		backbone->state.sticky = FALSE;
	
	if ( event->new_window_state &GDK_WINDOW_STATE_FULLSCREEN)
	{
		backbone->state.fullscreen = TRUE;
		//SENTINEL("fullscreen\n");
	}
	else
		backbone->state.fullscreen = FALSE;
	
	if ( event->new_window_state &GDK_WINDOW_STATE_ABOVE)
	{
		backbone->state.above = TRUE;
		//SENTINEL("above\n");
	}
	else
		backbone->state.above = FALSE;
	
	if ( event->new_window_state &GDK_WINDOW_STATE_BELOW)
	{
		backbone->state.below = TRUE;
		//SENTINEL("below\n");
	}
	else
		backbone->state.below = FALSE;
	
	return FALSE;
}
*/
/*void apply_window_configuration(GtkWidget * window, backbone_t * backbone)
{
	gtk_window_set_title(GTK_WINDOW(window), backbone->window.title->str);
	gtk_window_set_wmclass(GTK_WINDOW(backbone->window.widget), backbone->window.wm_name->str, backbone->window.wm_class->str); 
  gtk_window_set_role(GTK_WINDOW(window), backbone->window.role->str);
	if ( backbone->window.width != 0 && backbone->window.height != 0)
		gtk_window_resize (GTK_WINDOW(window), backbone->window.width, backbone->window.height);
	//Remove window decoration caution !! remove resize controls too
	gtk_window_set_decorated (GTK_WINDOW(window), backbone->window.decorated);
}
*/
