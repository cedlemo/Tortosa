#include <stdlib.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include "window.h"
#include "tabs.h"
#include "menus.h"
#include "events.h"
#include "gears.h"
#include "backbone.h"
#include "dbg.h"

int main(int argc, char ** argv)
{
	gtk_init(&argc, &argv);
	
	backbone_t * backbone = new_backbone();
	char tortosa[] = "Tortosa";
	
	GString * home;
	home = g_string_new(g_get_home_dir());
	backbone->configuration.dir_path = g_string_new( g_string_append(home,"/.config/tortosa")->str);
	backbone->configuration.file_path = g_string_new(g_string_append(backbone->configuration.dir_path, "/tortosarc")->str);
	g_string_free(home, TRUE);
	
	load_config(backbone);
	
	precompile_regex(backbone);
	
	backbone->display = gdk_display_get_default ();
	backbone->screen = gdk_display_get_default_screen (backbone->display);
	backbone->provider = gtk_css_provider_new ();
	gtk_style_context_add_provider_for_screen (	backbone->screen, 
																							GTK_STYLE_PROVIDER (backbone->provider), 
																							GTK_STYLE_PROVIDER_PRIORITY_USER);

	/***************/	
	/* Main Window */
	/***************/
	backbone->window.widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_wmclass(GTK_WINDOW(backbone->window.widget), backbone->window.wm_name->str, backbone->window.wm_class->str); 
	if( gtk_window_set_default_icon_from_file(DATADIR"/tortosa/tortosa.png", NULL) == FALSE)
		gtk_window_set_default_icon_name("terminal");
	//set window transparent if system supports it:
	init_window_visual_with_alpha(backbone->window.widget, backbone);
	apply_window_configuration(backbone->window.widget, backbone);
	
	g_signal_connect(backbone->window.widget, "destroy", G_CALLBACK(gtk_main_quit), NULL); 
	g_signal_connect(backbone->window.widget, "window-state-event", G_CALLBACK(get_window_state), backbone); //get window state events, this is used by fullscreen, above/below, iconify, maximize ... actions	
	g_signal_connect(G_OBJECT(backbone->window.widget), "draw", G_CALLBACK(draw_window_background), backbone); //redraw window background when needed
	g_signal_connect(backbone->window.widget, "screen-changed", G_CALLBACK(init_window_visual_with_alpha), backbone); //re-define the visual of the window if this one move to another screen
	g_signal_connect(backbone->provider, "parsing-error", G_CALLBACK(display_css_error_parsing), backbone); //display a warning if there are errors in the css file when loading/re-loading it.
	g_signal_connect(backbone->window.widget, "key-press-event", G_CALLBACK(event_key_press), backbone);
	
	/*css*/
	if ( backbone->css.file != NULL)
	{
			gtk_css_provider_load_from_file( GTK_CSS_PROVIDER (backbone->provider), backbone->css.file, NULL);
	}
	
	/**********************/
	/* Notebook container */
	/**********************/

	backbone->notebook.widget = gtk_notebook_new();
	gtk_notebook_set_scrollable(GTK_NOTEBOOK(backbone->notebook.widget), TRUE);
	apply_tabs_configuration(backbone);
	gtk_container_add (GTK_CONTAINER (backbone->window.widget), backbone->notebook.widget);

	/********************/
	/* Create first tab */
	/********************/

	new_tab(backbone);
	gtk_widget_show_all(backbone->window.widget);
	/**********************/
	/* Create menus */
	/**********************/

	create_resize_menu(backbone);
	create_reload_menu(backbone);
	create_main_menu(backbone);	
	gtk_main();
	return EXIT_SUCCESS;
}
//TODO create custom menu that depends on flavor
//TODO create .pc file with autotools
//TODO make some test for window operation with non gnome desktop
//TODO create gdk_shape
//TODO create doxygen documentation
//TODO write log macro without files/lines information and check if debug flag to swith
