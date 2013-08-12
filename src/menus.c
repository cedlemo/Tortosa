#include <stdlib.h>
#include <gtk/gtk.h>
#include "window.h"
#include "tabs.h"
#include "menus.h"
#include "gears.h"
#include "backbone.h"
#include "dbg.h"

void create_main_menu(backbone_t* backbone)
{
	backbone->main_menu = gtk_menu_new();
	GtkWidget * fullscreen = gtk_menu_item_new_with_label("toggle fullscreen");
	GtkWidget * above_below = gtk_menu_item_new_with_label("toggle above/below");
	GtkWidget * iconify = gtk_menu_item_new_with_label("toggle iconify");
	GtkWidget * stick = gtk_menu_item_new_with_label("toggle stick");
	GtkWidget * maximize = gtk_menu_item_new_with_label("toggle maximize");
	GtkWidget * grab_move = gtk_menu_item_new_with_label("grab/move");
	
	GtkWidget * resize = gtk_menu_item_new_with_label("resize");
	GtkWidget * reload = gtk_menu_item_new_with_label("reload");	

	GtkWidget * copy = gtk_menu_item_new_with_label("Copy");
	GtkWidget * paste = gtk_menu_item_new_with_label("Paste");
	
	GtkWidget * separator1 = gtk_separator_menu_item_new();
	GtkWidget * separator2 = gtk_separator_menu_item_new();
	GtkWidget * separator3 = gtk_separator_menu_item_new();

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(resize), backbone->resize_menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(reload), backbone->reload_menu);
	
	gtk_menu_attach(GTK_MENU(backbone->main_menu), reload, 0,1,0,1);
	gtk_menu_attach(GTK_MENU(backbone->main_menu), separator1, 0,1,1,2);
	gtk_menu_attach(GTK_MENU(backbone->main_menu), fullscreen, 0,1,2,3);
	gtk_menu_attach(GTK_MENU(backbone->main_menu), above_below, 0,1,3,4);
	gtk_menu_attach(GTK_MENU(backbone->main_menu), iconify, 0,1,4,5);
	gtk_menu_attach(GTK_MENU(backbone->main_menu), stick, 0,1,5,6);
	gtk_menu_attach(GTK_MENU(backbone->main_menu), grab_move, 0,1,6,7);
	gtk_menu_attach(GTK_MENU(backbone->main_menu), maximize, 0,1,7,8);
	gtk_menu_attach(GTK_MENU(backbone->main_menu), separator2, 0,1,8,9);
	gtk_menu_attach(GTK_MENU(backbone->main_menu), resize, 0,1,9,10);
	gtk_menu_attach(GTK_MENU(backbone->main_menu), separator3, 0,1,10,11);
	gtk_menu_attach(GTK_MENU(backbone->main_menu), copy, 0,1,11,12);
	gtk_menu_attach(GTK_MENU(backbone->main_menu), paste, 0,1,12,13);
	g_signal_connect_swapped(G_OBJECT(fullscreen), "activate", G_CALLBACK(toggle_fullscreen), backbone);
	g_signal_connect_swapped(G_OBJECT(above_below), "activate", G_CALLBACK(toggle_above_below), backbone);
	g_signal_connect_swapped(G_OBJECT(iconify), "activate", G_CALLBACK(toggle_iconify), backbone);
	g_signal_connect_swapped(G_OBJECT(stick), "activate", G_CALLBACK(toggle_stick), backbone);
	g_signal_connect_swapped(G_OBJECT(maximize), "activate", G_CALLBACK(toggle_maximize), backbone);
	g_signal_connect_swapped(G_OBJECT(grab_move), "activate", G_CALLBACK(grab_move_window), backbone);
	g_signal_connect_swapped(G_OBJECT(copy), "activate", G_CALLBACK(copy_selected_text_to_clipboard), backbone);
	g_signal_connect_swapped(G_OBJECT(paste), "activate", G_CALLBACK(paste_clipboard_to_vte_child), backbone);
	gtk_widget_show_all(backbone->main_menu);
}

void display_main_menu(guint32 time, backbone_t *backbone)
{
	/*found the Copy menuitem*/
	GList * menuitems = NULL;
	GtkWidget * copyitem;
	menuitems = gtk_container_get_children(GTK_CONTAINER(backbone->main_menu));
	/*iterate over all items and find the menuitem with label "Copy"*/
	gint length = g_list_length(menuitems);
	menuitems = g_list_first(menuitems);
	int i=0;
	for(i=0; i< length; i++)
	{
		if ( g_strcmp0(gtk_menu_item_get_label(GTK_MENU_ITEM(menuitems->data)), "Copy") == 0)
		{
			copyitem=GTK_WIDGET(menuitems->data);
			break;
		}
		menuitems = g_list_next(menuitems);
	}
	
		
		if(vte_terminal_get_has_selection(VTE_TERMINAL(gtk_notebook_get_nth_page(	GTK_NOTEBOOK(backbone->notebook.widget), 
																																							gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->notebook.widget))
																																						)
																									)) == FALSE)	
		/*Set copy menu item inactive if no text is selected*/
		
			gtk_widget_set_sensitive(GTK_WIDGET(copyitem), FALSE);
		else
			gtk_widget_set_sensitive(GTK_WIDGET(copyitem), TRUE);
		
		GdkDeviceManager *device_manager;
		GdkDevice *device;
		gint x, y;
	
		device_manager = gdk_display_get_device_manager (gtk_widget_get_display (backbone->window.widget));
		device = gdk_device_manager_get_client_pointer (device_manager);
		
		gtk_menu_popup_for_device( GTK_MENU(backbone->main_menu),
                               device,
                               NULL,
                               NULL,
                               NULL,
                               NULL,
                               NULL,
                               0,
                               time);

}

void create_reload_menu(backbone_t *backbone)
{
	backbone->reload_menu = gtk_menu_new();
	GtkWidget * reload_window = gtk_menu_item_new_with_label("window conf");
	GtkWidget * reload_tabs = gtk_menu_item_new_with_label("tabs conf");
	GtkWidget * reload_css = gtk_menu_item_new_with_label("css theme");
	GtkWidget * reload_vte = gtk_menu_item_new_with_label("vte conf");
	GtkWidget * reload_tortosa = gtk_menu_item_new_with_label("all");
	gtk_menu_attach(GTK_MENU(backbone->reload_menu), reload_window, 0,1,0,1);
	gtk_menu_attach(GTK_MENU(backbone->reload_menu), reload_tabs, 0,1,1,2);
	gtk_menu_attach(GTK_MENU(backbone->reload_menu), reload_vte, 0,1,2,3);
	gtk_menu_attach(GTK_MENU(backbone->reload_menu), reload_css, 0,1,3,4);
	gtk_menu_attach(GTK_MENU(backbone->reload_menu), reload_tortosa, 0,1,4,5);
	g_signal_connect_swapped(G_OBJECT(reload_tortosa), "activate", G_CALLBACK(reload_tortosa_configuration), backbone);
	g_signal_connect_swapped(G_OBJECT(reload_window), "activate", G_CALLBACK(reload_window_configuration), backbone);
	g_signal_connect_swapped(G_OBJECT(reload_tabs), "activate", G_CALLBACK(reload_tabs_configuration), backbone);
	g_signal_connect_swapped(G_OBJECT(reload_css), "activate", G_CALLBACK(reload_css_theme), backbone);
	g_signal_connect_swapped(G_OBJECT(reload_vte), "activate", G_CALLBACK(reload_vte_configuration), backbone);
	gtk_widget_show_all(backbone->reload_menu);
}

#define EDGE_GRABER( edge, gravity)\
static gboolean grab_resize_##edge(GtkWidget *widget, backbone_t * backbone)\
{\
	GdkWindow * parent_win;\
	parent_win = gdk_window_get_effective_parent(GDK_WINDOW(gtk_widget_get_window((backbone->window.widget))));\
	GdkDeviceManager *device_manager;\
	GdkDevice *pointer;\
	gint x, y;\
	device_manager = gdk_display_get_device_manager (gdk_window_get_display (parent_win));\
  pointer = gdk_device_manager_get_client_pointer (device_manager);\
  gdk_window_get_device_position (GDK_WINDOW(/*gtk_widget_get_window(backbone->window.widget)*/parent_win), pointer, &x, &y, NULL);\
	gtk_widget_grab_focus(backbone->window.widget);\
	gtk_window_begin_resize_drag( GTK_WINDOW(backbone->window.widget),\
                                  gravity,\
                                  1,\
                                  x,\
                                  y,\
                                  backbone->time);\
	return TRUE;\
}
EDGE_GRABER(left,GDK_WINDOW_EDGE_WEST) 
EDGE_GRABER(right,GDK_WINDOW_EDGE_EAST) 
EDGE_GRABER(top,GDK_WINDOW_EDGE_NORTH) 
EDGE_GRABER(bottom,GDK_WINDOW_EDGE_SOUTH) 
EDGE_GRABER(top_left,GDK_WINDOW_EDGE_NORTH_WEST) 
EDGE_GRABER(top_right,GDK_WINDOW_EDGE_NORTH_EAST) 
EDGE_GRABER(bottom_left,GDK_WINDOW_EDGE_SOUTH_WEST) 
EDGE_GRABER(bottom_right,GDK_WINDOW_EDGE_SOUTH_EAST) 
#undef EDGE_GRABBER

void create_resize_menu(backbone_t * backbone)
{
		backbone->resize_menu = gtk_menu_new();
		//gtk_widget_set_name(backbone->resize_menu, "resizeMenu");
		GtkWidget * top = gtk_menu_item_new_with_label("top");
		GtkWidget * bottom = gtk_menu_item_new_with_label("bottom");
		GtkWidget * left = gtk_menu_item_new_with_label("left");
		GtkWidget * right = gtk_menu_item_new_with_label("right");
		GtkWidget * top_left = gtk_menu_item_new_with_label("top-left");
		GtkWidget * top_right = gtk_menu_item_new_with_label("top-right");
		GtkWidget * bottom_left = gtk_menu_item_new_with_label("bottom-left");
		GtkWidget * bottom_right = gtk_menu_item_new_with_label("bottom_right");
		/*gtk_menu_attach(GTK_MENU(backbone->resize_menu), top_left, 0,1,0,1);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), top, 2,3,0,1);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), top_right, 4,5,0,1);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), left, 0,2,2,3);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), right, 3,5,2,3);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), bottom_left, 0,1,3,4);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), bottom, 2,3,3,4);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), bottom_right, 4,5,3,4);
		*/
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), top, 0,1,0,1);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), bottom, 0,1,1,2);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), left, 0,1,2,3);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), right, 0,1,3,4);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), top_left, 0,1,4,5);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), top_right, 0,1,5,6);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), bottom_left, 0,1,6,7);
		gtk_menu_attach(GTK_MENU(backbone->resize_menu), bottom_right, 0,1,7,8);

		g_signal_connect(G_OBJECT(top), "activate", G_CALLBACK(grab_resize_top), backbone);
		g_signal_connect(G_OBJECT(bottom), "activate", G_CALLBACK(grab_resize_bottom), backbone);
		g_signal_connect(G_OBJECT(left), "activate", G_CALLBACK(grab_resize_left), backbone);
		g_signal_connect(G_OBJECT(right), "activate", G_CALLBACK(grab_resize_right),backbone);
		g_signal_connect(G_OBJECT(top_left), "activate", G_CALLBACK(grab_resize_top_left),backbone);
		g_signal_connect(G_OBJECT(top_right), "activate", G_CALLBACK(grab_resize_top_right),backbone);
		g_signal_connect(G_OBJECT(bottom_left), "activate", G_CALLBACK(grab_resize_bottom_left),backbone);
		g_signal_connect(G_OBJECT(bottom_right), "activate", G_CALLBACK(grab_resize_bottom_right),backbone);
		
		gtk_widget_show_all(backbone->resize_menu);	
}

void display_resize_menu(guint32 time, backbone_t *backbone)
{
		GdkDeviceManager *device_manager;
		GdkDevice *device;
		gint x, y;
	
		device_manager = gdk_display_get_device_manager (gtk_widget_get_display (backbone->window.widget));
		device = gdk_device_manager_get_client_pointer (device_manager);
		
		gtk_menu_popup_for_device( GTK_MENU(backbone->resize_menu),
                               device,
                               NULL,
                               NULL,
                               NULL,
                               NULL,
                               NULL,
                               0,
                               time);
}

