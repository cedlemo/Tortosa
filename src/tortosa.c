#include <stdlib.h>
#include <getopt.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include "window.h"
#include "tabs.h"
#include "menus.h"
#include "events.h"
#include "gears.h"
#include "backbone.h"
#include "dbg.h"
#include "tgregex.h"

int main(int argc, char ** argv)
{
	
	/*Manage command line parameters*/
	static struct option tortosa_options[] =
	{
	   { "help",		no_argument, NULL, 'h' }, // display help
	   { "version", no_argument, NULL, 'v' }, // display version
	   { "config",	required_argument, NULL, 'c' }, // use specified file as configuration file
	   { "execute", required_argument, NULL, 'e' }, // command to execute 
	   { NULL,      0, NULL, 0 }    // no options
	};
	GString * arg_configuration_file = NULL;
	GString * arg_command_to_execute = NULL;
	int opt;
	while((opt = getopt_long(argc, argv, "hvc:e:", tortosa_options, NULL)) != -1)
		switch(opt)
		{
			case 'v':
				printf("✔ Tortosa Terminal Beta\n");
				exit(EXIT_SUCCESS);
				break;
			case 'h':
				printf("✔ Tortosa Terminal Beta help:\n");
				exit(EXIT_SUCCESS);
				break;
			case 'e':
				printf("Execute :%s\n",optarg);
				arg_command_to_execute = g_string_new(optarg);
				//exit(EXIT_SUCCESS);
				break;
			case 'c':
				printf("Fichier de configuration :%s\n",optarg);
				arg_configuration_file = g_string_new(optarg);
				//exit(EXIT_SUCCESS);
				break;
		}

	
	gtk_init(&argc, &argv);
	
	backbone_t * backbone = new_backbone();
	backbone->args.configuration_file = arg_configuration_file;
	backbone->args.command_to_execute = arg_command_to_execute;
	
	char tortosa[] = "Tortosa";
	
	GString * home;
	home = g_string_new(g_get_home_dir());
	backbone->configuration.dir_path = g_string_new( g_string_append(home,"/.config/tortosa")->str);
	
	if(arg_configuration_file)
		backbone->configuration.file_path = arg_configuration_file;
	else
		backbone->configuration.file_path = g_string_new(g_string_append(backbone->configuration.dir_path, "/tortosarc")->str);
	
	g_string_free(home, TRUE);
	
	load_config(backbone);
	//TODO rename	
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
	
	g_signal_connect_swapped(backbone->window.widget, "destroy", G_CALLBACK(quit_gracefully), backbone); 
	g_signal_connect(backbone->window.widget, "window-state-event", G_CALLBACK(get_window_state), backbone); //get window state events, this is used by fullscreen, above/below, iconify, maximize ... actions	
	g_signal_connect(G_OBJECT(backbone->window.widget), "draw", G_CALLBACK(draw_window_background), backbone); //redraw window background when needed
	g_signal_connect(backbone->window.widget, "screen-changed", G_CALLBACK(init_window_visual_with_alpha), backbone); //re-define the visual of the window if this one move to another screen
	g_signal_connect(backbone->provider, "parsing-error", G_CALLBACK(display_css_error_parsing), backbone); //display a warning if there are errors in the css file when loading/re-loading it.
	g_signal_connect(backbone->window.widget, "key-press-event", G_CALLBACK(event_key_press), backbone);
	
	/*css*/
	if ( backbone->css.file != NULL)
	{
		/*load css*/
		gtk_css_provider_load_from_file( GTK_CSS_PROVIDER (backbone->provider), backbone->css.file, NULL);
		/*compile css regexes for window background, notebook tab active color*/
		compile_css_regexes(backbone);
		/*get matches*/
		load_css_regexes_match(backbone);
		gtk_widget_queue_draw(backbone->window.widget);
	}
	
	/**********************/
	/* Notebook container */
	/**********************/

	backbone->notebook.widget = gtk_notebook_new();
	gtk_notebook_set_scrollable(GTK_NOTEBOOK(backbone->notebook.widget), TRUE);
	g_signal_connect(backbone->notebook.widget, "switch-page", G_CALLBACK(on_switch_tabs_signal), backbone);
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
