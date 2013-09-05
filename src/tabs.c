#include <stdlib.h>
#include <vte/vte.h>
#include <gtk/gtk.h>
#include "gears.h"
#include "backbone.h"
#include "tabs.h"
#include "events.h"
#include "tgregex.h"
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

static void remove_pango_active_tab_color(GtkWidget * vte, GtkNotebook * notebook)
{
	gtk_notebook_set_tab_label_text(GTK_NOTEBOOK(notebook), vte, gtk_notebook_get_tab_label_text(GTK_NOTEBOOK(notebook), vte));
}

static void add_pango_active_tab_color(GtkWidget * vte, GtkNotebook * notebook, GdkRGBA *color)
{
		GtkWidget * tab_label = gtk_notebook_get_tab_label(GTK_NOTEBOOK(notebook), vte);
		if (tab_label == NULL)
			return;
		char *markup;
		markup = g_markup_printf_escaped("<span color=\"#%02x%02x%02x\">%s</span>", (int) color->red*255,
																																								(int) color->green*255, 
																																								(int) color->blue*255, 
																																								gtk_label_get_text(GTK_LABEL(tab_label)));
		gtk_label_set_markup (GTK_LABEL(tab_label), markup);
		g_free (markup);

}

void on_switch_tabs_signal(GtkNotebook *notebook, GtkWidget   *last_vte, guint new_vte_index, backbone_t * backbone)
{
	
	if(gtk_notebook_get_current_page(notebook) != -1 )
	{	
		remove_pango_active_tab_color(gtk_notebook_get_nth_page(notebook,gtk_notebook_get_current_page(notebook)), notebook);
	}
	add_pango_active_tab_color(gtk_notebook_get_nth_page(notebook, new_vte_index), notebook, &backbone->notebook.active_tab.rgba);
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
	
	if(backbone->notebook.active_tab.color && vte == gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->notebook.widget), gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->notebook.widget)) ) )
	{
		add_pango_active_tab_color(vte, GTK_NOTEBOOK(backbone->notebook.widget), &backbone->notebook.active_tab.rgba);
	}
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
	const char * working_directory = NULL;
	GPid pid = 0;
	GtkWidget * vte;
	gchar **argvp=0;
	int argc;

	/*Check if it's not the first tab*/
	if( gtk_notebook_get_n_pages(GTK_NOTEBOOK(backbone->notebook.widget)) >= 1 )
	{
		/*Get the current directory of the focused vte in order to start the new vte in this directory*/
		GtkWidget * focused_vte = gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->notebook.widget), 
																												gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->notebook.widget))
																												);
		GSList *found = NULL;
		found = g_slist_find_custom(backbone->tabs_data, focused_vte, (GCompareFunc) find_node_by_widget);
		
		if (found)
			working_directory =  get_pid_dir(((tab_data_t*) found->data)->pid);
	
		/*parse vte arguments*/
		if ( g_shell_parse_argv(backbone->vte.command->str, &argc, &argvp,0) != TRUE )
		{
			g_shell_parse_argv(g_getenv("SHELL"), &argc, &argvp,0);
		}
	}
	else
	{
		/*This is the first tab*/
		/*check command line argument for command to execute and parse vte arguments*/
		if(backbone->args.command_to_execute)
		{
			if ( g_shell_parse_argv(backbone->args.command_to_execute->str, &argc, &argvp,0) != TRUE )
			{
				g_shell_parse_argv(g_getenv("SHELL"), &argc, &argvp,0);
			}
		}
		else
		{
			if ( g_shell_parse_argv(backbone->vte.command->str, &argc, &argvp,0) != TRUE )
			{
				g_shell_parse_argv(g_getenv("SHELL"), &argc, &argvp,0);
			}
		}
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
	{
		LOG_ERR("%s\n", error->message);
		g_strfreev(argvp);
		/*TODO make a clean exit*/
		exit(EXIT_FAILURE);
	}
	g_strfreev(argvp);

	/*register our tabs data in the tabs_data GSList*/
	tab_data_t * tab_data = g_new0(tab_data_t, 1);
	tab_data->widget = vte;
	tab_data->pid = pid;
	tab_data->match_tags = NULL;
	tab_data->current_match = NULL;
	tab_data->current_flavor = 666; /*a number not in the enum range*/

	int i;
  for (i = 0; i < backbone->regexes.number; ++i)
  {
		TagData *tag_data;
		tag_data = g_slice_new (TagData);
		tag_data->flavor = backbone->regexes.flavors[i];
		tag_data->tag = vte_terminal_match_add_gregex(VTE_TERMINAL(vte), backbone->regexes.g_regexes[i], 0);
		tab_data->match_tags = g_slist_prepend( tab_data->match_tags, tag_data);
	}
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

void copy_regex_match_to_vte_clipboard(backbone_t * backbone)
{
	GtkWidget * vte = gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->notebook.widget), gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->notebook.widget)));

	GSList *found = NULL;
	found = g_slist_find_custom(backbone->tabs_data, vte, (GCompareFunc) find_node_by_widget);
	const gchar *match = NULL;
	if (found)
	{
		match = ((tab_data_t*) found->data)->current_match;
	}
	if(match)
	{
		GtkClipboard *clipboard;
		clipboard = gtk_widget_get_clipboard(GTK_WIDGET(backbone->window.widget), GDK_SELECTION_CLIPBOARD);
		gtk_clipboard_set_text(clipboard, match, -1);
	}
}
