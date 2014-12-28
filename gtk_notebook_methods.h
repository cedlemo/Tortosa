#ifndef GTK_NOTEBOOK_METHODS_H
#define GTK_NOTEBOOK_METHODS_H
#include <ruby.h>
#include <gtk/gtk.h>
#include "backbone.h"
void gtk_notebook_wrapper(VALUE);
#endif
/*|--------------------------------------->>*/
/* functions wrapped                        */
/*<<---------------------------------------|*/
//gtk_notebook_remove_page
//gtk_notebook_set_group_name
//gtk_notebook_get_group_name
//gtk_notebook_get_current_page
//gtk_notebook_get_n_pages
//gtk_notebook_set_current_page
//gtk_notebook_next_page
//gtk_notebook_prev_page
//gtk_notebook_set_show_border
//gtk_notebook_get_show_border
//gtk_notebook_set_show_tabs
//gtk_notebook_get_show_tabs
//gtk_notebook_set_tab_pos
//gtk_notebook_set_scrollable
//gtk_notebook_get_scrollable
//gtk_notebook_popup_enable
//gtk_notebook_popup_disable
/*|--------------------------------------->>*/
/* functions ignored                        */
/*<<---------------------------------------|*/
//gtk_notebook_get_type
//gtk_notebook_new
//gtk_notebook_append_page
//gtk_notebook_append_page_menu
//gtk_notebook_prepend_page
//gtk_notebook_prepend_page_menu
//gtk_notebook_insert_page
//gtk_notebook_insert_page_menu
//gtk_notebook_get_nth_page
//gtk_notebook_page_num
//gtk_notebook_get_tab_pos
//gtk_notebook_get_tab_hborder
//gtk_notebook_get_tab_vborder
//gtk_notebook_get_tab_label
//gtk_notebook_set_tab_label
//gtk_notebook_set_tab_label_text
//gtk_notebook_get_tab_label_text
//gtk_notebook_get_menu_label
//gtk_notebook_set_menu_label
//gtk_notebook_set_menu_label_text
//gtk_notebook_get_menu_label_text
//gtk_notebook_reorder_child
//gtk_notebook_get_tab_reorderable
//gtk_notebook_set_tab_reorderable
//gtk_notebook_get_tab_detachable
//gtk_notebook_set_tab_detachable
//gtk_notebook_get_action_widget
//gtk_notebook_set_action_widget
