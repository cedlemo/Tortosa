#ifndef GTK_WINDOW_METHODS_H
#define GTK_WINDOW_METHODS_H
#include <ruby.h>
#include <gtk/gtk.h>
#include <vte/vte.h>
#include "backbone.h"
#include "dbg.h"
typedef struct window_t {
  GtkWidget * widget;
} window_t;
VALUE generate_window_ruby_class_under(VALUE, VALUE); 
#endif

/*|--------------------------------------->>*/
/* functions wrapped                        */
/*<<---------------------------------------|*/
//gtk_window_set_title
//gtk_window_get_title
//gtk_window_set_wmclass
//gtk_window_set_role
//gtk_window_set_startup_id
//gtk_window_get_role
//gtk_window_activate_focus
//gtk_window_activate_default
//gtk_window_get_type_hint
//gtk_window_set_skip_taskbar_hint
//gtk_window_get_skip_taskbar_hint
//gtk_window_set_skip_pager_hint
//gtk_window_get_skip_pager_hint
//gtk_window_set_urgency_hint
//gtk_window_get_urgency_hint
//gtk_window_set_accept_focus
//gtk_window_get_accept_focus
//gtk_window_set_focus_on_map
//gtk_window_get_focus_on_map
//gtk_window_set_destroy_with_parent
//gtk_window_get_destroy_with_parent
//gtk_window_set_hide_titlebar_when_maximized
//gtk_window_get_hide_titlebar_when_maximized
//gtk_window_set_mnemonics_visible
//gtk_window_get_mnemonics_visible
//gtk_window_set_focus_visible
//gtk_window_get_focus_visible
//gtk_window_set_resizable
//gtk_window_get_resizable
//gtk_window_is_active
//gtk_window_has_toplevel_focus
//gtk_window_set_decorated
//gtk_window_get_decorated
//gtk_window_set_deletable
//gtk_window_get_deletable
//gtk_window_set_icon_name
//gtk_window_get_icon_name
//gtk_window_set_default_icon_name
//gtk_window_get_default_icon_name
//gtk_window_set_auto_startup_notification
//gtk_window_set_modal
//gtk_window_get_modal
//gtk_window_set_has_user_ref_count
//gtk_window_present
//gtk_window_iconify
//gtk_window_deiconify
//gtk_window_stick
//gtk_window_unstick
//gtk_window_maximize
//gtk_window_unmaximize
//gtk_window_fullscreen
//gtk_window_unfullscreen
//gtk_window_close
//gtk_window_set_keep_above
//gtk_window_set_keep_below
//gtk_window_set_default_size
//gtk_window_get_default_size
//gtk_window_resize
//gtk_window_get_size
//gtk_window_move
//gtk_window_get_position
//gtk_window_parse_geometry
//gtk_window_set_default_geometry
//gtk_window_resize_to_geometry
//gtk_window_has_group
//gtk_window_is_maximized
//gtk_window_set_interactive_debugging
/*|--------------------------------------->>*/
/* functions ignored                        */
/*<<---------------------------------------|*/
//gtk_window_get_type
//gtk_window_new
//gtk_window_add_accel_group
//gtk_window_remove_accel_group
//gtk_window_set_position
//gtk_window_set_focus
//gtk_window_get_focus
//gtk_window_set_default
//gtk_window_get_default_widget
//gtk_window_set_transient_for
//gtk_window_get_transient_for
//gtk_window_set_attached_to
//gtk_window_get_attached_to
//gtk_window_set_opacity
//gtk_window_get_opacity
//gtk_window_set_type_hint
//gtk_window_set_gravity
//gtk_window_get_gravity
//gtk_window_set_geometry_hints
//gtk_window_set_screen
//gtk_window_get_screen
//gtk_window_set_icon_list
//gtk_window_get_icon_list
//gtk_window_set_icon
//gtk_window_set_icon_from_file
//gtk_window_get_icon
//gtk_window_set_default_icon_list
//gtk_window_get_default_icon_list
//gtk_window_set_default_icon
//gtk_window_set_default_icon_from_file
//gtk_window_list_toplevels
//gtk_window_add_mnemonic
//gtk_window_remove_mnemonic
//gtk_window_mnemonic_activate
//gtk_window_set_mnemonic_modifier
//gtk_window_get_mnemonic_modifier
//gtk_window_activate_key
//gtk_window_propagate_key_event
//gtk_window_present_with_time
//gtk_window_begin_resize_drag
//gtk_window_begin_move_drag
//gtk_window_get_group
//gtk_window_reshow_with_initial_size
//gtk_window_get_window_type
//gtk_window_get_application
//gtk_window_set_application
//gtk_window_set_has_resize_grip
//gtk_window_get_has_resize_grip
//gtk_window_resize_grip_is_visible
//gtk_window_get_resize_grip_area
//gtk_window_set_titlebar
