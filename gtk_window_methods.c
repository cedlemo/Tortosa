#include "gtk_window_methods.h"
static VALUE rtortosa_set_title(VALUE self, VALUE title){
  if(TYPE(title) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * r_title=RSTRING_PTR(title);
  gtk_window_set_title(GTK_WINDOW(backbone.window.widget),r_title);
  return Qnil;
}
static VALUE rtortosa_get_title(VALUE self){
  const gchar * ret =gtk_window_get_title(GTK_WINDOW(backbone.window.widget));
  return rb_strnew2(ret);
}
static VALUE rtortosa_set_wmclass(VALUE self, VALUE wmclass_name, VALUE wmclass_class){
  if(TYPE(wmclass_name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * r_wmclass_name=RSTRING_PTR(wmclass_name);
  if(TYPE(wmclass_class) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * r_wmclass_class=RSTRING_PTR(wmclass_class);
  gtk_window_set_wmclass(GTK_WINDOW(backbone.window.widget),r_wmclass_name,r_wmclass_class);
  return Qnil;
}
static VALUE rtortosa_set_role(VALUE self, VALUE role){
  if(TYPE(role) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * r_role=RSTRING_PTR(role);
  gtk_window_set_role(GTK_WINDOW(backbone.window.widget),r_role);
  return Qnil;
}
static VALUE rtortosa_set_startup_id(VALUE self, VALUE startup_id){
  if(TYPE(startup_id) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * r_startup_id=RSTRING_PTR(startup_id);
  gtk_window_set_startup_id(GTK_WINDOW(backbone.window.widget),r_startup_id);
  return Qnil;
}
static VALUE rtortosa_get_role(VALUE self){
  const gchar * ret =gtk_window_get_role(GTK_WINDOW(backbone.window.widget));
  return rb_strnew2(ret);
}
static VALUE rtortosa_activate_focus(VALUE self){
  gboolean ret =gtk_window_activate_focus(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_activate_default(VALUE self){
  gboolean ret =gtk_window_activate_default(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_skip_taskbar_hint(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_get_skip_taskbar_hint(VALUE self){
  gboolean ret =gtk_window_get_skip_taskbar_hint(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_skip_pager_hint(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_skip_pager_hint(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_get_skip_pager_hint(VALUE self){
  gboolean ret =gtk_window_get_skip_pager_hint(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_urgency_hint(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_urgency_hint(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_get_urgency_hint(VALUE self){
  gboolean ret =gtk_window_get_urgency_hint(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_accept_focus(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_accept_focus(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_get_accept_focus(VALUE self){
  gboolean ret =gtk_window_get_accept_focus(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_focus_on_map(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_focus_on_map(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_get_focus_on_map(VALUE self){
  gboolean ret =gtk_window_get_focus_on_map(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_destroy_with_parent(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_destroy_with_parent(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_get_destroy_with_parent(VALUE self){
  gboolean ret =gtk_window_get_destroy_with_parent(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_hide_titlebar_when_maximized(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_hide_titlebar_when_maximized(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_get_hide_titlebar_when_maximized(VALUE self){
  gboolean ret =gtk_window_get_hide_titlebar_when_maximized(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_mnemonics_visible(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_mnemonics_visible(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_get_mnemonics_visible(VALUE self){
  gboolean ret =gtk_window_get_mnemonics_visible(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_focus_visible(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_focus_visible(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_get_focus_visible(VALUE self){
  gboolean ret =gtk_window_get_focus_visible(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_resizable(VALUE self, VALUE resizable){
  gboolean r_resizable= (resizable == Qtrue) ? TRUE : FALSE;
  gtk_window_set_resizable(GTK_WINDOW(backbone.window.widget),r_resizable);
  return Qnil;
}
static VALUE rtortosa_get_resizable(VALUE self){
  gboolean ret =gtk_window_get_resizable(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_is_active(VALUE self){
  gboolean ret =gtk_window_is_active(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_has_toplevel_focus(VALUE self){
  gboolean ret =gtk_window_has_toplevel_focus(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_decorated(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_decorated(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_get_decorated(VALUE self){
  gboolean ret =gtk_window_get_decorated(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_deletable(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_deletable(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_get_deletable(VALUE self){
  gboolean ret =gtk_window_get_deletable(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_icon_name(VALUE self, VALUE name){
  if(TYPE(name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * r_name=RSTRING_PTR(name);
  gtk_window_set_icon_name(GTK_WINDOW(backbone.window.widget),r_name);
  return Qnil;
}
static VALUE rtortosa_get_icon_name(VALUE self){
  const gchar * ret =gtk_window_get_icon_name(GTK_WINDOW(backbone.window.widget));
  return rb_strnew2(ret);
}
static VALUE rtortosa_set_default_icon_name(VALUE self, VALUE name){
  if(TYPE(name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * r_name=RSTRING_PTR(name);
  gtk_window_set_default_icon_name(r_name);
  return Qnil;
}
static VALUE rtortosa_get_default_icon_name(VALUE self){
  const gchar * ret =gtk_window_get_default_icon_name();
  return rb_strnew2(ret);
}
static VALUE rtortosa_set_auto_startup_notification(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_auto_startup_notification(r_setting);
  return Qnil;
}
static VALUE rtortosa_set_modal(VALUE self, VALUE modal){
  gboolean r_modal= (modal == Qtrue) ? TRUE : FALSE;
  gtk_window_set_modal(GTK_WINDOW(backbone.window.widget),r_modal);
  return Qnil;
}
static VALUE rtortosa_get_modal(VALUE self){
  gboolean ret =gtk_window_get_modal(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_has_user_ref_count(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_has_user_ref_count(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_present(VALUE self){
  gtk_window_present(GTK_WINDOW(backbone.window.widget));
  return Qnil;
}
static VALUE rtortosa_iconify(VALUE self){
  gtk_window_iconify(GTK_WINDOW(backbone.window.widget));
  return Qnil;
}
static VALUE rtortosa_deiconify(VALUE self){
  gtk_window_deiconify(GTK_WINDOW(backbone.window.widget));
  return Qnil;
}
static VALUE rtortosa_stick(VALUE self){
  gtk_window_stick(GTK_WINDOW(backbone.window.widget));
  return Qnil;
}
static VALUE rtortosa_unstick(VALUE self){
  gtk_window_unstick(GTK_WINDOW(backbone.window.widget));
  return Qnil;
}
static VALUE rtortosa_maximize(VALUE self){
  gtk_window_maximize(GTK_WINDOW(backbone.window.widget));
  return Qnil;
}
static VALUE rtortosa_unmaximize(VALUE self){
  gtk_window_unmaximize(GTK_WINDOW(backbone.window.widget));
  return Qnil;
}
static VALUE rtortosa_fullscreen(VALUE self){
  gtk_window_fullscreen(GTK_WINDOW(backbone.window.widget));
  return Qnil;
}
static VALUE rtortosa_unfullscreen(VALUE self){
  gtk_window_unfullscreen(GTK_WINDOW(backbone.window.widget));
  return Qnil;
}
static VALUE rtortosa_close(VALUE self){
  gtk_window_close(GTK_WINDOW(backbone.window.widget));
  return Qnil;
}
static VALUE rtortosa_set_keep_above(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_keep_above(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_set_keep_below(VALUE self, VALUE setting){
  gboolean r_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_keep_below(GTK_WINDOW(backbone.window.widget),r_setting);
  return Qnil;
}
static VALUE rtortosa_set_default_size(VALUE self, VALUE width, VALUE height){
  if (TYPE(width) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  gint r_width=FIX2INT(width);
  if (TYPE(height) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  gint r_height=FIX2INT(height);
  gtk_window_set_default_size(GTK_WINDOW(backbone.window.widget),r_width,r_height);
  return Qnil;
}
static VALUE rtortosa_get_default_size(VALUE self){
  gint width;
      gint * r_width = &width;
  gint height;
      gint * r_height = &height;
  gtk_window_get_default_size(GTK_WINDOW(backbone.window.widget),r_width,r_height);
  VALUE ret= rb_ary_new();
  rb_ary_push(ret, INT2FIX(width));
  rb_ary_push(ret, INT2FIX(height));
return ret;
}
static VALUE rtortosa_resize(VALUE self, VALUE width, VALUE height){
  if (TYPE(width) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  gint r_width=FIX2INT(width);
  if (TYPE(height) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  gint r_height=FIX2INT(height);
  gtk_window_resize(GTK_WINDOW(backbone.window.widget),r_width,r_height);
  return Qnil;
}
static VALUE rtortosa_get_size(VALUE self){
  gint width;
      gint * r_width = &width;
  gint height;
      gint * r_height = &height;
  gtk_window_get_size(GTK_WINDOW(backbone.window.widget),r_width,r_height);
  VALUE ret= rb_ary_new();
  rb_ary_push(ret, INT2FIX(width));
  rb_ary_push(ret, INT2FIX(height));
return ret;
}
static VALUE rtortosa_move(VALUE self, VALUE x, VALUE y){
  if (TYPE(x) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  gint r_x=FIX2INT(x);
  if (TYPE(y) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  gint r_y=FIX2INT(y);
  gtk_window_move(GTK_WINDOW(backbone.window.widget),r_x,r_y);
  return Qnil;
}
static VALUE rtortosa_get_position(VALUE self){
  gint root_x;
      gint * r_root_x = &root_x;
  gint root_y;
      gint * r_root_y = &root_y;
  gtk_window_get_position(GTK_WINDOW(backbone.window.widget),r_root_x,r_root_y);
  VALUE ret= rb_ary_new();
  rb_ary_push(ret, INT2FIX(root_x));
  rb_ary_push(ret, INT2FIX(root_y));
return ret;
}
static VALUE rtortosa_parse_geometry(VALUE self, VALUE geometry){
  if(TYPE(geometry) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * r_geometry=RSTRING_PTR(geometry);
  gboolean ret =gtk_window_parse_geometry(GTK_WINDOW(backbone.window.widget),r_geometry);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_default_geometry(VALUE self, VALUE width, VALUE height){
  if (TYPE(width) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  gint r_width=FIX2INT(width);
  if (TYPE(height) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  gint r_height=FIX2INT(height);
  gtk_window_set_default_geometry(GTK_WINDOW(backbone.window.widget),r_width,r_height);
  return Qnil;
}
static VALUE rtortosa_resize_to_geometry(VALUE self, VALUE width, VALUE height){
  if (TYPE(width) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  gint r_width=FIX2INT(width);
  if (TYPE(height) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  gint r_height=FIX2INT(height);
  gtk_window_resize_to_geometry(GTK_WINDOW(backbone.window.widget),r_width,r_height);
  return Qnil;
}
static VALUE rtortosa_has_group(VALUE self){
  gboolean ret =gtk_window_has_group(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_is_maximized(VALUE self){
  gboolean ret =gtk_window_is_maximized(GTK_WINDOW(backbone.window.widget));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_set_interactive_debugging(VALUE self, VALUE enable){
  gboolean r_enable= (enable == Qtrue) ? TRUE : FALSE;
  gtk_window_set_interactive_debugging(r_enable);
  return Qnil;
}
void gtk_window_wrapper(VALUE module){
  rb_define_module_function(module, 
                                        "set_title", 
                                        rtortosa_set_title,
                                        1);
  rb_define_module_function(module, 
                                        "get_title", 
                                        rtortosa_get_title,
                                        0);
  rb_define_module_function(module, 
                                        "set_wmclass", 
                                        rtortosa_set_wmclass,
                                        2);
  rb_define_module_function(module, 
                                        "set_role", 
                                        rtortosa_set_role,
                                        1);
  rb_define_module_function(module, 
                                        "set_startup_id", 
                                        rtortosa_set_startup_id,
                                        1);
  rb_define_module_function(module, 
                                        "get_role", 
                                        rtortosa_get_role,
                                        0);
  rb_define_module_function(module, 
                                        "activate_focus", 
                                        rtortosa_activate_focus,
                                        0);
  rb_define_module_function(module, 
                                        "activate_default", 
                                        rtortosa_activate_default,
                                        0);
  rb_define_module_function(module, 
                                        "set_skip_taskbar_hint", 
                                        rtortosa_set_skip_taskbar_hint,
                                        1);
  rb_define_module_function(module, 
                                        "get_skip_taskbar_hint", 
                                        rtortosa_get_skip_taskbar_hint,
                                        0);
  rb_define_module_function(module, 
                                        "set_skip_pager_hint", 
                                        rtortosa_set_skip_pager_hint,
                                        1);
  rb_define_module_function(module, 
                                        "get_skip_pager_hint", 
                                        rtortosa_get_skip_pager_hint,
                                        0);
  rb_define_module_function(module, 
                                        "set_urgency_hint", 
                                        rtortosa_set_urgency_hint,
                                        1);
  rb_define_module_function(module, 
                                        "get_urgency_hint", 
                                        rtortosa_get_urgency_hint,
                                        0);
  rb_define_module_function(module, 
                                        "set_accept_focus", 
                                        rtortosa_set_accept_focus,
                                        1);
  rb_define_module_function(module, 
                                        "get_accept_focus", 
                                        rtortosa_get_accept_focus,
                                        0);
  rb_define_module_function(module, 
                                        "set_focus_on_map", 
                                        rtortosa_set_focus_on_map,
                                        1);
  rb_define_module_function(module, 
                                        "get_focus_on_map", 
                                        rtortosa_get_focus_on_map,
                                        0);
  rb_define_module_function(module, 
                                        "set_destroy_with_parent", 
                                        rtortosa_set_destroy_with_parent,
                                        1);
  rb_define_module_function(module, 
                                        "get_destroy_with_parent", 
                                        rtortosa_get_destroy_with_parent,
                                        0);
  rb_define_module_function(module, 
                                        "set_hide_titlebar_when_maximized", 
                                        rtortosa_set_hide_titlebar_when_maximized,
                                        1);
  rb_define_module_function(module, 
                                        "get_hide_titlebar_when_maximized", 
                                        rtortosa_get_hide_titlebar_when_maximized,
                                        0);
  rb_define_module_function(module, 
                                        "set_mnemonics_visible", 
                                        rtortosa_set_mnemonics_visible,
                                        1);
  rb_define_module_function(module, 
                                        "get_mnemonics_visible", 
                                        rtortosa_get_mnemonics_visible,
                                        0);
  rb_define_module_function(module, 
                                        "set_focus_visible", 
                                        rtortosa_set_focus_visible,
                                        1);
  rb_define_module_function(module, 
                                        "get_focus_visible", 
                                        rtortosa_get_focus_visible,
                                        0);
  rb_define_module_function(module, 
                                        "set_resizable", 
                                        rtortosa_set_resizable,
                                        1);
  rb_define_module_function(module, 
                                        "get_resizable", 
                                        rtortosa_get_resizable,
                                        0);
  rb_define_module_function(module, 
                                        "is_active", 
                                        rtortosa_is_active,
                                        0);
  rb_define_module_function(module, 
                                        "has_toplevel_focus", 
                                        rtortosa_has_toplevel_focus,
                                        0);
  rb_define_module_function(module, 
                                        "set_decorated", 
                                        rtortosa_set_decorated,
                                        1);
  rb_define_module_function(module, 
                                        "get_decorated", 
                                        rtortosa_get_decorated,
                                        0);
  rb_define_module_function(module, 
                                        "set_deletable", 
                                        rtortosa_set_deletable,
                                        1);
  rb_define_module_function(module, 
                                        "get_deletable", 
                                        rtortosa_get_deletable,
                                        0);
  rb_define_module_function(module, 
                                        "set_icon_name", 
                                        rtortosa_set_icon_name,
                                        1);
  rb_define_module_function(module, 
                                        "get_icon_name", 
                                        rtortosa_get_icon_name,
                                        0);
  rb_define_module_function(module, 
                                        "set_default_icon_name", 
                                        rtortosa_set_default_icon_name,
                                        1);
  rb_define_module_function(module, 
                                        "get_default_icon_name", 
                                        rtortosa_get_default_icon_name,
                                        0);
  rb_define_module_function(module, 
                                        "set_auto_startup_notification", 
                                        rtortosa_set_auto_startup_notification,
                                        1);
  rb_define_module_function(module, 
                                        "set_modal", 
                                        rtortosa_set_modal,
                                        1);
  rb_define_module_function(module, 
                                        "get_modal", 
                                        rtortosa_get_modal,
                                        0);
  rb_define_module_function(module, 
                                        "set_has_user_ref_count", 
                                        rtortosa_set_has_user_ref_count,
                                        1);
  rb_define_module_function(module, 
                                        "present", 
                                        rtortosa_present,
                                        0);
  rb_define_module_function(module, 
                                        "iconify", 
                                        rtortosa_iconify,
                                        0);
  rb_define_module_function(module, 
                                        "deiconify", 
                                        rtortosa_deiconify,
                                        0);
  rb_define_module_function(module, 
                                        "stick", 
                                        rtortosa_stick,
                                        0);
  rb_define_module_function(module, 
                                        "unstick", 
                                        rtortosa_unstick,
                                        0);
  rb_define_module_function(module, 
                                        "maximize", 
                                        rtortosa_maximize,
                                        0);
  rb_define_module_function(module, 
                                        "unmaximize", 
                                        rtortosa_unmaximize,
                                        0);
  rb_define_module_function(module, 
                                        "fullscreen", 
                                        rtortosa_fullscreen,
                                        0);
  rb_define_module_function(module, 
                                        "unfullscreen", 
                                        rtortosa_unfullscreen,
                                        0);
  rb_define_module_function(module, 
                                        "close", 
                                        rtortosa_close,
                                        0);
  rb_define_module_function(module, 
                                        "set_keep_above", 
                                        rtortosa_set_keep_above,
                                        1);
  rb_define_module_function(module, 
                                        "set_keep_below", 
                                        rtortosa_set_keep_below,
                                        1);
  rb_define_module_function(module, 
                                        "set_default_size", 
                                        rtortosa_set_default_size,
                                        2);
  rb_define_module_function(module, 
                                        "get_default_size", 
                                        rtortosa_get_default_size,
                                        0);
  rb_define_module_function(module, 
                                        "resize", 
                                        rtortosa_resize,
                                        2);
  rb_define_module_function(module, 
                                        "get_size", 
                                        rtortosa_get_size,
                                        0);
  rb_define_module_function(module, 
                                        "move", 
                                        rtortosa_move,
                                        2);
  rb_define_module_function(module, 
                                        "get_position", 
                                        rtortosa_get_position,
                                        0);
  rb_define_module_function(module, 
                                        "parse_geometry", 
                                        rtortosa_parse_geometry,
                                        1);
  rb_define_module_function(module, 
                                        "set_default_geometry", 
                                        rtortosa_set_default_geometry,
                                        2);
  rb_define_module_function(module, 
                                        "resize_to_geometry", 
                                        rtortosa_resize_to_geometry,
                                        2);
  rb_define_module_function(module, 
                                        "has_group", 
                                        rtortosa_has_group,
                                        0);
  rb_define_module_function(module, 
                                        "is_maximized", 
                                        rtortosa_is_maximized,
                                        0);
  rb_define_module_function(module, 
                                        "set_interactive_debugging", 
                                        rtortosa_set_interactive_debugging,
                                        1);
}
