#include <stdlib.h>
#include <vte/vte.h>
#include "gears.h"
#include "backbone.h"
#include "colors.h"
#include "dbg.h"

/*Stuff for creating and freeing backbone*/
backbone_t * new_backbone( void)
{
	backbone_t * backbone;
	backbone = (backbone_t *) malloc( sizeof(backbone_t) );
	
	if ( backbone == NULL)
	{
		LOG_ERR("Malloc Failed");
		exit(EXIT_FAILURE);
	}
	backbone->state.withdrawn = FALSE;
	backbone->state.iconified = FALSE;
	backbone->state.maximized = FALSE;
	backbone->state.sticky = FALSE;
	backbone->state.fullscreen = FALSE;
	backbone->state.above = FALSE;
	backbone->state.below = FALSE;
	backbone->args.command_to_execute = NULL;
	return backbone;
}

void free_backbone( backbone_t * backbone)
{
	//SENTINEL("Free window stuff\n");
	FREE_GSTRING(backbone->window.title);
	FREE_GSTRING(backbone->window.wm_class);
	FREE_GSTRING(backbone->window.wm_name);
	FREE_GSTRING(backbone->window.role);
	FREE_GSTRING(backbone->window.background.color);

  FREE_GSTRING(backbone->command.line);	
	//FREE_GSTRING(backbone->configuration.dir_path);
	//FREE_GSTRING(backbone->configuration.file_path);
	/*no need to free args.configuration_file (already freed with FREE_GSTRING(backbone->configuration.file_path);*/
	//FREE_GSTRING(backbone->args.command_to_execute);

	//SENTINEL("Free main backbone\n");
	//free((void *) backbone);
}

void quit_gracefully(backbone_t * backbone)
{
	free_backbone(backbone);
  gtk_main_quit();
}

void set_default_config(backbone_t *backbone)
{
	backbone->window.title=g_string_new("Tortosa");
	backbone->window.wm_class=g_string_new("Tortosa");
	backbone->window.wm_name=g_string_new("Tortosa");
	backbone->window.role=g_string_new("Tortosa");
	backbone->window.width=0;
	backbone->window.height=0;
	backbone->window.decorated=TRUE;
	backbone->window.background.color=g_string_new("#00000000");
	extended_gdk_rgba_parse( &backbone->window.background.rgba, backbone->window.background.color->str);
}

/*Check the window manager*/
/*gboolean window_manager_is_gnome_like(GdkScreen * screen)
{
	const char cinnamon[]="Mutter (Muffin)";
	const char gnomeshell[]="GNOME Shell";
	const char * current_WM = gdk_x11_screen_get_window_manager_name(screen);
	SENTINEL("%s\n", current_WM);
	gboolean is_gnome_like = FALSE;

	if ( g_strcmp0(current_WM, cinnamon) == 0)
		is_gnome_like = TRUE;
	if ( g_strcmp0(current_WM, gnomeshell) == 0)
		is_gnome_like = TRUE;

	return is_gnome_like;
}*/
