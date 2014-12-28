#ifndef GTK_VTE_METHODS_H
#define GTK_VTE_METHODS_H
#include <ruby.h>
#include <gtk/gtk.h>
#include <vte/vte.h>
#include "tabs.h"
#include "backbone.h"
#include "dbg.h"
typedef struct vte_t {
  GtkWidget * vte;
  char * working_directory;
  VALUE command;
  GPid pid;
} vte_t;
VALUE generate_vte_ruby_class_under(VALUE); 
#endif

/*|--------------------------------------->>*/
/* functions wrapped                        */
/*<<---------------------------------------|*/
//vte_terminal_copy_clipboard
//vte_terminal_paste_clipboard
//vte_terminal_copy_primary
//vte_terminal_paste_primary
//vte_terminal_select_all
//vte_terminal_unselect_all
//vte_terminal_set_size
//vte_terminal_set_font_scale
//vte_terminal_get_font_scale
//vte_terminal_set_audible_bell
//vte_terminal_get_audible_bell
//vte_terminal_set_scroll_on_output
//vte_terminal_set_scroll_on_keystroke
//vte_terminal_set_rewrap_on_resize
//vte_terminal_get_rewrap_on_resize
//vte_terminal_set_color_bold
//vte_terminal_set_color_foreground
//vte_terminal_set_color_background
//vte_terminal_set_color_cursor
//vte_terminal_set_color_highlight
//vte_terminal_set_color_highlight_foreground
//vte_terminal_set_default_colors
//vte_terminal_set_scrollback_lines
//vte_terminal_set_allow_bold
//vte_terminal_get_allow_bold
//vte_terminal_get_has_selection
//vte_terminal_set_mouse_autohide
//vte_terminal_get_mouse_autohide
//vte_terminal_reset
//vte_terminal_get_cursor_position
//vte_terminal_get_encoding
//vte_terminal_get_cjk_ambiguous_width
//vte_terminal_get_char_width
//vte_terminal_get_char_height
//vte_terminal_get_row_count
//vte_terminal_get_column_count
//vte_terminal_get_window_title
//vte_terminal_get_icon_title
//vte_terminal_get_current_directory_uri
//vte_terminal_get_current_file_uri
//vte_terminal_set_input_enabled
//vte_terminal_get_input_enabled
/*|--------------------------------------->>*/
/* functions ignored                        */
/*<<---------------------------------------|*/
//vte_terminal_get_type
//vte_terminal_new
//vte_terminal_pty_new_sync
//vte_terminal_watch_child
//vte_terminal_spawn_sync
//vte_terminal_feed
//vte_terminal_feed_child
//vte_terminal_feed_child_binary
//vte_terminal_set_colors
//vte_terminal_set_cursor_blink_mode
//vte_terminal_get_cursor_blink_mode
//vte_terminal_set_cursor_shape
//vte_terminal_get_cursor_shape
//vte_terminal_set_font
//vte_terminal_get_font
//vte_terminal_set_backspace_binding
//vte_terminal_set_delete_binding
//vte_terminal_get_text
//vte_terminal_get_text_include_trailing_spaces
//vte_terminal_get_text_range
//vte_terminal_match_add_gregex
//vte_terminal_match_set_cursor
//vte_terminal_match_set_cursor_type
//vte_terminal_match_set_cursor_name
//vte_terminal_match_remove
//vte_terminal_match_remove_all
//vte_terminal_match_check
//vte_terminal_match_check_event
//vte_terminal_search_set_gregex
//vte_terminal_search_get_gregex
//vte_terminal_search_set_wrap_around
//vte_terminal_search_get_wrap_around
//vte_terminal_search_find_previous
//vte_terminal_search_find_next
//vte_terminal_set_encoding
//vte_terminal_set_cjk_ambiguous_width
//vte_terminal_set_pty
//vte_terminal_get_pty
//vte_terminal_get_geometry_hints
//vte_terminal_set_geometry_hints_for_window
//vte_terminal_write_contents_sync
