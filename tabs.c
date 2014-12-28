#include "tabs.h"
static void go_to_tab_plus_n(GtkNotebook *n, gint increment)
{
  int current_tab, next_tab_index, num_of_tabs;
  current_tab = gtk_notebook_get_current_page(n) ;
  num_of_tabs = gtk_notebook_get_n_pages(n) - 1;
  switch(increment)
  {
    case 1:
      next_tab_index = current_tab < num_of_tabs ? current_tab + increment : 0;
      break;
    case -1:
      next_tab_index = current_tab > 0 ? current_tab + increment : 0;
      break;
    default:
      break;
  }
  gtk_notebook_set_current_page(n, next_tab_index);
  gtk_widget_grab_focus( gtk_notebook_get_nth_page(n, next_tab_index) );

}
void go_to_next_tab(GtkNotebook *n)
{
  go_to_tab_plus_n(n, 1);
}

void go_to_prev_tab(GtkNotebook *n)
{
  go_to_tab_plus_n(n, (-1));
}

