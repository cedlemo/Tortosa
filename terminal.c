#include "terminal.h"
#include "gears.h"
#include "dbg.h"

static void close_tab_on_exit(GtkWidget * vte, gint status, backbone_t * backbone)
{
  gint current = gtk_notebook_get_current_page (GTK_NOTEBOOK(backbone->window.notebook));
  if (gtk_notebook_get_n_pages (GTK_NOTEBOOK(backbone->window.notebook)) > 1)
  {
    gtk_notebook_remove_page (GTK_NOTEBOOK(backbone->window.notebook), current );
    gtk_widget_grab_focus(
      gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->window.notebook),
       gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->window.notebook))));
  
  }
  else
  {
    quit_gracefully(backbone);
  }
  SENTINEL("%d", status);  
}
static gchar* get_pid_dir(GPid pid)
{
  gchar* file = g_strdup_printf("/proc/%d/cwd", pid);
  gchar* link = g_file_read_link(file, NULL);
  g_free(file);
  return link;
}

void new_terminal_emulator( backbone_t * backbone, gchar *command_to_exec)
{
  const char * working_directory = NULL;
  GPid pid = 0;
  GtkWidget * vte;
  gchar **argvp=0;
  int argc;
 
  const gchar *command;
  command = command_to_exec? command_to_exec : g_getenv("SHELL");
  if(g_shell_parse_argv(command, &argc, &argvp,0) != TRUE )
    g_shell_parse_argv(g_getenv("SHELL"), &argc, &argvp,0);
  /*Check if it's not the first tab in order to have the pid_dir*/
  //if( gtk_notebook_get_n_pages(GTK_NOTEBOOK(backbone->window.notebook)) >= 1 )
  //{
    /*Get the current directory of the focused vte in order to start the new vte in this directory*/
   // GtkWidget * focused_vte = gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->window.notebook), 
   //                                                     gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->window.notebook))
   //                                                     );
    /*parse vte arguments*/
    //if ( g_shell_parse_argv(backbone->vte.command->str, &argc, &argvp,0) != TRUE )
    //{
    //  g_shell_parse_argv(g_getenv("SHELL"), &argc, &argvp,0);
    //}
  //}
  //else
  //{
    /*This is the first tab*/
    /*check command line argument for command to execute and parse vte arguments*/
//    if(backbone->args.command_to_execute)
//    {
//      if ( g_shell_parse_argv(backbone->args.command_to_execute->str, &argc, &argvp,0) != TRUE )
//      {
//        g_shell_parse_argv(g_getenv("SHELL"), &argc, &argvp,0);
//      }
//    }
//    else
//    {
//      if ( g_shell_parse_argv(backbone->vte.command->str, &argc, &argvp,0) != TRUE )
//      {
//        g_shell_parse_argv(g_getenv("SHELL"), &argc, &argvp,0);
//      }
//    }
  //}

  GError *error = NULL;
  vte = vte_terminal_new();
  if( !vte_terminal_spawn_sync( VTE_TERMINAL(vte),
                                  VTE_PTY_DEFAULT,
                                  working_directory,
                                  argvp,
                                  NULL,
                                  G_SPAWN_SEARCH_PATH,
                                  NULL,
                                  NULL,
                                  &pid,
                                  NULL,
                                  &error))
  {
    LOG_ERR("%s\n", error->message);
    g_strfreev(argvp);
    /*TODO make a clean exit*/
    rb_raise(rb_eTypeError, "Unable to create a vte terminal");
  }
  g_strfreev(argvp);

  /*register our tabs data in the tabs_data GSList*/
//  tab_data_t * tab_data = g_new0(tab_data_t, 1);
//  tab_data->widget = vte;
//  tab_data->pid = pid;
//  tab_data->match_tags = NULL;
//  tab_data->current_match = NULL;
//  tab_data->current_flavor = 666; /*a number not in the enum range*/

//  int i;
//  for (i = 0; i < backbone->regexes.number; ++i)
//  {
//    TagData *tag_data;
//    tag_data = g_slice_new (TagData);
//    tag_data->flavor = backbone->regexes.flavors[i];
//    tag_data->tag = vte_terminal_match_add_gregex(VTE_TERMINAL(vte), backbone->regexes.g_regexes[i], 0);
//    tab_data->match_tags = g_slist_prepend( tab_data->match_tags, tag_data);
//  }
//  backbone->tabs_data = g_slist_append(backbone->tabs_data, tab_data);


  g_signal_connect(vte, "child-exited", G_CALLBACK(close_tab_on_exit), backbone);

  int index = gtk_notebook_append_page(GTK_NOTEBOOK(backbone->window.notebook), vte, NULL);
  gtk_notebook_set_tab_reorderable( GTK_NOTEBOOK(backbone->window.notebook),
                                    vte, 
                                    TRUE);
  
//  set_tab_name(vte, backbone);
  
//  g_signal_connect(vte, "window-title-changed", G_CALLBACK(set_tab_name),backbone);

  gtk_widget_show_all(backbone->window.notebook);
  gtk_notebook_set_current_page(GTK_NOTEBOOK(backbone->window.notebook), index);
  gtk_widget_grab_focus(vte);
}

