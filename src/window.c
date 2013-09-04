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
		return FALSE;
	}
  return FALSE;
/*Must always return false otherwise tabs are not displayed don't know why*/
}

void toggle_above_below(backbone_t * backbone)
{
	if (backbone->state.above)
	{
		gtk_window_set_keep_above(GTK_WINDOW(backbone->window.widget), FALSE);
		gtk_window_set_keep_below(GTK_WINDOW(backbone->window.widget), TRUE);
		backbone->state.above = FALSE;
		backbone->state.below = TRUE;
	}
	else
	{	
		gtk_window_set_keep_below(GTK_WINDOW(backbone->window.widget), FALSE);
		gtk_window_set_keep_above(GTK_WINDOW(backbone->window.widget), TRUE);
		backbone->state.above = TRUE;
		backbone->state.below = FALSE;
	}
}

void toggle_fullscreen(backbone_t * backbone)
{
	if (backbone->state.fullscreen)
	{
		gtk_window_unfullscreen(GTK_WINDOW(backbone->window.widget));
		backbone->state.fullscreen = FALSE;
	}
	else
	{
		gtk_window_fullscreen(GTK_WINDOW(backbone->window.widget));
		backbone->state.fullscreen = TRUE;
	}
}

void toggle_iconify(backbone_t * backbone)
{
	if (backbone->state.iconified)
	{
		gtk_window_deiconify(GTK_WINDOW(backbone->window.widget));
		backbone->state.iconified = FALSE;
	}
	else
	{
		gtk_window_iconify(GTK_WINDOW(backbone->window.widget));
		backbone->state.iconified = TRUE;
	}
}

void toggle_stick(backbone_t * backbone)
{
	if (backbone->state.sticky)
	{
		gtk_window_unstick(GTK_WINDOW(backbone->window.widget));
		backbone->state.sticky = FALSE;
	}
	else
	{
		gtk_window_stick(GTK_WINDOW(backbone->window.widget));
		backbone->state.sticky = TRUE;
	}
}

void toggle_maximize(backbone_t * backbone)
{
	if (backbone->state.maximized)
	{
		gtk_window_unmaximize(GTK_WINDOW(backbone->window.widget));
		backbone->state.maximized = FALSE;
	}
	else
	{
		gtk_window_maximize(GTK_WINDOW(backbone->window.widget));
		backbone->state.maximized = TRUE;
	}
}

void grab_move_window(backbone_t * backbone)
{
	GdkWindow * parent_win;
	parent_win = gdk_window_get_effective_parent(GDK_WINDOW(gtk_widget_get_window((backbone->window.widget))));
	GdkDeviceManager *device_manager;
	GdkDevice *pointer;
	gint x, y;
	device_manager = gdk_display_get_device_manager (gdk_window_get_display (parent_win));
  pointer = gdk_device_manager_get_client_pointer (device_manager);
  gdk_window_get_device_position (GDK_WINDOW(parent_win), pointer, &x, &y, NULL);
	gtk_window_begin_move_drag(GTK_WINDOW(backbone->window.widget),
  1,
	x,
	y,
	backbone->time);
}

void reload_css_theme( backbone_t * backbone)
{
	if ( backbone->css.file != NULL)
	{
		gtk_css_provider_load_from_file( GTK_CSS_PROVIDER (backbone->provider), backbone->css.file, NULL/*&error*/);
		load_css_regexes_match(backbone);
	}
	else
	{
		LOG_WARN("No css file to reload check your tortosarc file.\n");
	}
	gtk_widget_queue_draw (GTK_WIDGET (backbone->window.widget));
}

gboolean display_css_error_parsing(GtkCssProvider *provider, GtkCssSection  *section, GError *error, backbone_t *backbone)
{
	if (error)
		LOG_WARN("error in %s:%d:%d  %s", backbone->css.path->str, gtk_css_section_get_end_line(section) + 1, gtk_css_section_get_end_position(section),error->message);

	return FALSE;
}

void apply_window_configuration(GtkWidget * window, backbone_t * backbone)
{
	gtk_window_set_title(GTK_WINDOW(window), backbone->window.title->str);
	gtk_window_set_role(GTK_WINDOW(window), backbone->window.role->str);
	if ( backbone->window.width != 0 && backbone->window.height != 0)
		gtk_window_resize (GTK_WINDOW(window), backbone->window.width, backbone->window.height);
	//Remove window decoration caution !! remove resize controls too
	gtk_window_set_decorated (GTK_WINDOW(window), backbone->window.decorated);
}

gboolean reload_window_configuration(backbone_t * backbone)
{
	if(backbone->configuration.keyfile)
		g_key_file_free(backbone->configuration.keyfile);
	gboolean ret;
	backbone->configuration.keyfile = g_key_file_new ();
	ret = g_key_file_load_from_file( backbone->configuration.keyfile,
																	 backbone->configuration.file_path->str,
																	 G_KEY_FILE_NONE,
																	 NULL);
	if (ret == FALSE)
	{	
		LOG_WARN("Unable to load the configuration file %s", backbone->configuration.file_path->str);
		g_key_file_free(backbone->configuration.keyfile);
		backbone->configuration.keyfile = NULL;
	}
	else	
	{	
		/*reset all previous configuration*/
		FREE_GSTRING(backbone->window.title);
		FREE_GSTRING(backbone->window.wm_class);
		FREE_GSTRING(backbone->window.wm_name);
		FREE_GSTRING(backbone->window.role);
		backbone->window.height = 0;
		backbone->window.width = 0;
		backbone->window.decorated = TRUE;
		FREE_GSTRING(backbone->window.background.color);
		/*reload current configuration for window*/
		load_window_configuration(backbone);	
		if ( backbone->css.file != NULL)
		{
			load_css_regexes_match(backbone);
	  }

		apply_window_configuration(backbone->window.widget, backbone);
		gtk_widget_queue_draw (GTK_WIDGET (backbone->window.widget));
		//gtk_widget_show_all(backbone->window.widget);
	}
	
	return ret;
}
