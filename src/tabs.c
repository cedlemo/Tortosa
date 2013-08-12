#include <stdlib.h>
#include <vte/vte.h>
#include <gtk/gtk.h>
#include "gears.h"
#include "backbone.h"
#include "tabs.h"
#include "events.h"
#include "dbg.h"

void close_tab(GtkWidget * vte, backbone_t * backbone)
{
	gint current = gtk_notebook_get_current_page (GTK_NOTEBOOK(backbone->notebook.widget));
	if (gtk_notebook_get_n_pages (GTK_NOTEBOOK(backbone->notebook.widget)) > 1)
	{
		/*Remove from GSList backbone->tabs_data*/
		remove_node_by_widget(backbone->tabs_data, gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->notebook.widget), gtk_notebook_get_current_page (GTK_NOTEBOOK(backbone->notebook.widget))));
		
		gtk_notebook_remove_page (GTK_NOTEBOOK(backbone->notebook.widget), current );
		gtk_widget_grab_focus(
		  gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->notebook.widget),
			 gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->notebook.widget))));
	
	}
	else
	{
		gtk_main_quit();
	}
}

void go_to_next_tab(backbone_t * backbone)
{
	int current_tab, next_tab_index, num_of_tabs;
	current_tab = gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->notebook.widget)) ;
	num_of_tabs = gtk_notebook_get_n_pages(GTK_NOTEBOOK(backbone->notebook.widget)) - 1;
	next_tab_index = current_tab < num_of_tabs ? current_tab + 1 : 0;
	gtk_widget_show_all(backbone->notebook.widget);
	gtk_notebook_set_current_page(GTK_NOTEBOOK(backbone->notebook.widget), next_tab_index);
	gtk_widget_grab_focus(gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->notebook.widget), next_tab_index));
}

void go_to_prev_tab(backbone_t * backbone)
{
	int current_tab, next_tab_index, num_of_tabs;
	current_tab = gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->notebook.widget)) ;
	num_of_tabs = gtk_notebook_get_n_pages(GTK_NOTEBOOK(backbone->notebook.widget)) - 1;
	next_tab_index = current_tab > 0 ? current_tab -1 : num_of_tabs;
	gtk_widget_show_all(backbone->notebook.widget);
	gtk_notebook_set_current_page(GTK_NOTEBOOK(backbone->notebook.widget), next_tab_index);
	gtk_widget_grab_focus(gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->notebook.widget), next_tab_index));
}

static void set_tab_name( GtkWidget * vte, backbone_t * backbone)
{
	const char * window_title = vte_terminal_get_window_title(VTE_TERMINAL(vte));
	
	if ( window_title != NULL && g_strcmp0(window_title,"" ) != 0)
	{
	GString * tab_label = g_string_new(window_title);
	if ( (backbone->notebook.tab_name_max_len != 0) && (tab_label->len > backbone->notebook.tab_name_max_len) )
		g_string_truncate(tab_label, backbone->notebook.tab_name_max_len);

		gtk_notebook_set_tab_label_text (	GTK_NOTEBOOK(backbone->notebook.widget),
                                    vte,
                                    tab_label->str);
		g_string_free(tab_label, TRUE);
	}
	else
	{
		GString * tab_label = g_string_new(backbone->notebook.default_tab_name->str); 
		gint index = gtk_notebook_page_num(GTK_NOTEBOOK(backbone->notebook.widget), vte);
		g_string_append(tab_label, g_strdup_printf(" %i", index));
		
		gtk_notebook_set_tab_label_text (	GTK_NOTEBOOK(backbone->notebook.widget),
                                    vte,
                                    tab_label->str);
	
		g_string_free(tab_label, TRUE);
	}
	gtk_notebook_popup_disable(GTK_NOTEBOOK(backbone->notebook.widget));
	gtk_notebook_popup_enable(GTK_NOTEBOOK(backbone->notebook.widget));
}

void apply_vte_configuration(backbone_t *backbone, GtkWidget * vte)
{
	if( backbone->vte.user_valid_palette )
	{
		int i;
		GdkRGBA palette[16];
		for(i=0; i<16; i++)
		{
			palette[i].red = backbone->vte.palette[i].rgba.red;
			palette[i].green = backbone->vte.palette[i].rgba.green;
			palette[i].blue = backbone->vte.palette[i].rgba.blue;
			palette[i].alpha = backbone->vte.palette[i].rgba.alpha;
		}
		vte_terminal_set_opacity (VTE_TERMINAL(vte), backbone->vte.opacity);
		vte_terminal_set_colors_rgba (VTE_TERMINAL(vte),
                                     &backbone->vte.foreground.rgba,
                                     &backbone->vte.background.rgba,
                                     palette,
                                     16);
	}
	else
	{
		vte_terminal_set_default_colors( VTE_TERMINAL(vte) );
		vte_terminal_set_opacity (VTE_TERMINAL(vte), 65535);
	}
	if (backbone->vte.font != NULL && g_strcmp0( backbone->vte.font->str, "") != 0 )
		vte_terminal_set_font_from_string( VTE_TERMINAL(vte), backbone->vte.font->str);
	
	if (backbone->vte.background_tint_color)
	{
		vte_terminal_set_background_saturation(VTE_TERMINAL(vte), backbone->vte.background_saturation);
		vte_terminal_set_background_tint_color(VTE_TERMINAL(vte), &backbone->vte.background_tint);
	}

	if(backbone->vte.background_image)
		vte_terminal_set_background_image_file(VTE_TERMINAL(vte), backbone->vte.background_image->str);
	else
		vte_terminal_set_background_image(VTE_TERMINAL(vte), NULL);
	
	vte_terminal_set_scrollback_lines(VTE_TERMINAL(vte), backbone->vte.scrollback_lines);
	if(backbone->vte.cursor_color.color)
		vte_terminal_set_color_cursor_rgba(VTE_TERMINAL(vte), &backbone->vte.cursor_color.rgba);
	else
		vte_terminal_set_color_cursor_rgba(VTE_TERMINAL(vte), NULL);
	vte_terminal_set_cursor_shape(VTE_TERMINAL(vte), backbone->vte.cursor_shape);
	vte_terminal_set_cursor_blink_mode(VTE_TERMINAL(vte), backbone->vte.cursor_blink);
	if(backbone->vte.highlight.color)
		vte_terminal_set_color_highlight_rgba(VTE_TERMINAL(vte), &backbone->vte.highlight.rgba);
	else
		vte_terminal_set_color_highlight_rgba(VTE_TERMINAL(vte), NULL);
	
	vte_terminal_set_visible_bell(VTE_TERMINAL(vte), backbone->vte.bell_visible);
	vte_terminal_set_audible_bell(VTE_TERMINAL(vte), backbone->vte.bell_audible);
}

gboolean reload_vte_configuration( backbone_t * backbone)
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
		/*release all preallocated colors*/
		backbone->vte.user_valid_palette=FALSE;
//		FREE_GSTRING(backbone->vte.foreground_color);
//		FREE_GSTRING(backbone->vte.background_color);
		FREE_GSTRING(backbone->vte.foreground.color);
		FREE_GSTRING(backbone->vte.background.color);
		FREE_GSTRING(backbone->vte.command);
		FREE_GSTRING(backbone->vte.background_image);
		int i =0;
		for( i =0; i<16; i++)
		{
			FREE_GSTRING(backbone->vte.palette[i].color);
		}
		FREE_GSTRING(backbone->vte.font);
		FREE_GSTRING(backbone->vte.background_tint_color);
		load_vte_configuration(backbone);
		
		gint nb_vte=gtk_notebook_get_n_pages(GTK_NOTEBOOK(backbone->notebook.widget));
		
		for(i=0; i< nb_vte; i++)
		{
			GtkWidget *vte = gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->notebook.widget), i);
			apply_vte_configuration(backbone, vte);
				gtk_widget_show(GTK_WIDGET (vte));
		}
	}

	return ret;
}

void apply_tabs_configuration( backbone_t * backbone)
{
	gtk_notebook_set_show_border(GTK_NOTEBOOK(backbone->notebook.widget), backbone->notebook.show_border);
	gtk_notebook_set_show_tabs (GTK_NOTEBOOK(backbone->notebook.widget), backbone->notebook.show_tabs);
	if(backbone->notebook.show_tabs == TRUE)
		gtk_notebook_set_tab_pos (GTK_NOTEBOOK(backbone->notebook.widget), backbone->notebook.tabs_position);

	gtk_notebook_popup_enable(GTK_NOTEBOOK(backbone->notebook.widget));
}

gboolean reload_tabs_configuration( backbone_t * backbone)
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
		backbone->notebook.show_border = TRUE;
		backbone->notebook.show_tabs = TRUE;
		backbone->notebook.tabs_position = GTK_POS_TOP;
		FREE_GSTRING(backbone->notebook.default_tab_name);
		backbone->notebook.tab_name_max_len=0;
		load_tabs_configuration(backbone);
		apply_tabs_configuration(backbone);
		gtk_widget_show(backbone->notebook.widget);
	}

	return ret;
}

static gchar* get_pid_dir(GPid pid)
{
  gchar* file = g_strdup_printf("/proc/%d/cwd", pid);
	gchar* link = g_file_read_link(file, NULL);
  g_free(file);
  return link;
}

void new_tab( backbone_t * backbone)
{
	const char * working_directory;
	
	GPid pid = 0;
	/*Check if it's not the first tab*/
	if( gtk_notebook_get_n_pages(GTK_NOTEBOOK(backbone->notebook.widget)) >= 1 )
	{
		/*Get the current directory of the focused vte*/
		GtkWidget * focused_vte = gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->notebook.widget), 
																												gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->notebook.widget))
																												);
		GSList *found = NULL;
		found = g_slist_find_custom(backbone->tabs_data, focused_vte, (GCompareFunc) find_node_by_widget);
		
		if (found)
		{
			working_directory =  get_pid_dir(((tab_data_t*) found->data)->pid);
		}
		else
		{
			working_directory = NULL;
		}
	}
	else
	{
		working_directory = NULL;
	}

	GtkWidget * vte;
	pid = 0;
	gchar **argvp=0;
	int argc;
	if ( g_shell_parse_argv(backbone->vte.command->str, &argc, &argvp,0) != TRUE )
	{
		g_shell_parse_argv(g_getenv("SHELL"), &argc, &argvp,0);
	}
	
	GError *error = NULL;
	vte = vte_terminal_new();
	if( !vte_terminal_fork_command_full( VTE_TERMINAL(vte),
																	VTE_PTY_DEFAULT,
																	working_directory,
																	argvp,
																	NULL,
																	G_SPAWN_SEARCH_PATH,
																	NULL,
																	NULL,
																	&pid,
																	&error))
		LOG_WARN("%s\n", error->message);
	
	g_strfreev(argvp);

	/*register our tabs data in the tabs_data GSList*/
	tab_data_t * tab_data = g_new0(tab_data_t, 1);
	tab_data->widget = vte;
	tab_data->pid = pid;
	backbone->tabs_data = g_slist_append(backbone->tabs_data, tab_data);

	g_signal_connect(vte, "child-exited", G_CALLBACK(close_tab), backbone);
	g_signal_connect(vte, "button-press-event", G_CALLBACK(event_button_press), backbone);	

	apply_vte_configuration(backbone, vte);
	
	int index = gtk_notebook_append_page(GTK_NOTEBOOK(backbone->notebook.widget), vte, NULL);
	gtk_notebook_set_tab_reorderable(	GTK_NOTEBOOK(backbone->notebook.widget),
																		vte, 
																		TRUE);
	
	set_tab_name(vte, backbone);
	
	g_signal_connect(vte, "window-title-changed", G_CALLBACK(set_tab_name),backbone);

	gtk_widget_show_all(backbone->notebook.widget);
	gtk_notebook_set_current_page(GTK_NOTEBOOK(backbone->notebook.widget), index);
	gtk_widget_grab_focus(vte);
}

void copy_selected_text_to_clipboard(backbone_t * backbone)
{
	/*get current vte*/
		GtkWidget * focused_vte = gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->notebook.widget), 
																												gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->notebook.widget))
																												);
	vte_terminal_copy_clipboard(VTE_TERMINAL(focused_vte));
}

void paste_clipboard_to_vte_child(backbone_t * backbone)
{
	/*get current vte*/
		GtkWidget * focused_vte = gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->notebook.widget), 
																												gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->notebook.widget))
																												);
	vte_terminal_paste_clipboard(VTE_TERMINAL(focused_vte));
}
