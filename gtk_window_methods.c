/*notebook ruby class*/
#include "gtk_window_methods.h"

static void c_window_struct_free(window_t *c)
{
  if(c)
  {
    ruby_xfree(c);
  }
}
static VALUE c_window_struct_alloc( VALUE klass)
{
  return Data_Wrap_Struct(klass, NULL, c_window_struct_free, ruby_xmalloc(sizeof(window_t)));
}
/*static VALUE c_window_initialize(VALUE self, VALUE command)
{
}*/
static VALUE rtortosa_window_set_title(VALUE self,VALUE title){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  if(TYPE(title) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_title=RSTRING_PTR(title);
  gtk_window_set_title(window,c_title);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_title(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  const gchar * c_ret =gtk_window_get_title(window);
  VALUE r_ret = rb_str_new2(c_ret);

  return r_ret;

}
static VALUE rtortosa_window_set_wmclass(VALUE self,VALUE wmclass_name,VALUE wmclass_class){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  if(TYPE(wmclass_name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_wmclass_name=RSTRING_PTR(wmclass_name);
  if(TYPE(wmclass_class) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_wmclass_class=RSTRING_PTR(wmclass_class);
  gtk_window_set_wmclass(window,c_wmclass_name,c_wmclass_class);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_set_role(VALUE self,VALUE role){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  if(TYPE(role) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_role=RSTRING_PTR(role);
  gtk_window_set_role(window,c_role);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_set_startup_id(VALUE self,VALUE startup_id){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  if(TYPE(startup_id) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_startup_id=RSTRING_PTR(startup_id);
  gtk_window_set_startup_id(window,c_startup_id);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_role(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  const gchar * c_ret =gtk_window_get_role(window);
  VALUE r_ret = rb_str_new2(c_ret);

  return r_ret;

}
static VALUE rtortosa_window_activate_focus(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_activate_focus(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_activate_default(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_activate_default(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_get_type_hint(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  GdkWindowTypeHint c_ret =gtk_window_get_type_hint(window);
  VALUE r_ret = INT2NUM((int) c_ret);

  return r_ret;

}
static VALUE rtortosa_window_set_skip_taskbar_hint(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_skip_taskbar_hint(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_skip_taskbar_hint(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_skip_taskbar_hint(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_skip_pager_hint(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_skip_pager_hint(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_skip_pager_hint(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_skip_pager_hint(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_urgency_hint(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_urgency_hint(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_urgency_hint(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_urgency_hint(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_accept_focus(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_accept_focus(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_accept_focus(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_accept_focus(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_focus_on_map(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_focus_on_map(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_focus_on_map(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_focus_on_map(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_destroy_with_parent(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_destroy_with_parent(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_destroy_with_parent(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_destroy_with_parent(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_hide_titlebar_when_maximized(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_hide_titlebar_when_maximized(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_hide_titlebar_when_maximized(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_hide_titlebar_when_maximized(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_mnemonics_visible(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_mnemonics_visible(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_mnemonics_visible(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_mnemonics_visible(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_focus_visible(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_focus_visible(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_focus_visible(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_focus_visible(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_resizable(VALUE self,VALUE resizable){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_resizable= (resizable == Qtrue) ? TRUE : FALSE;
  gtk_window_set_resizable(window,c_resizable);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_resizable(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_resizable(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_is_active(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_is_active(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_has_toplevel_focus(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_has_toplevel_focus(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_decorated(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_decorated(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_decorated(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_decorated(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_deletable(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_deletable(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_deletable(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_deletable(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_icon_name(VALUE self,VALUE name){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  if(TYPE(name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_name=RSTRING_PTR(name);
  gtk_window_set_icon_name(window,c_name);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_icon_name(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  const gchar * c_ret =gtk_window_get_icon_name(window);
  VALUE r_ret = rb_str_new2(c_ret);

  return r_ret;

}
static VALUE rtortosa_window_set_default_icon_name(VALUE name){
  if(TYPE(name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_name=RSTRING_PTR(name);
  gtk_window_set_default_icon_name(c_name);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_default_icon_name(){
  const gchar * c_ret =gtk_window_get_default_icon_name();
  VALUE r_ret = rb_str_new2(c_ret);

  return r_ret;

}
static VALUE rtortosa_window_set_auto_startup_notification(VALUE setting){
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_auto_startup_notification(c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_set_modal(VALUE self,VALUE modal){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_modal= (modal == Qtrue) ? TRUE : FALSE;
  gtk_window_set_modal(window,c_modal);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_modal(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_get_modal(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_has_user_ref_count(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_has_user_ref_count(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_present(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gtk_window_present(window);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_iconify(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gtk_window_iconify(window);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_deiconify(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gtk_window_deiconify(window);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_stick(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gtk_window_stick(window);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_unstick(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gtk_window_unstick(window);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_maximize(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gtk_window_maximize(window);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_unmaximize(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gtk_window_unmaximize(window);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_fullscreen(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gtk_window_fullscreen(window);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_unfullscreen(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gtk_window_unfullscreen(window);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_close(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gtk_window_close(window);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_set_keep_above(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_keep_above(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_set_keep_below(VALUE self,VALUE setting){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  gtk_window_set_keep_below(window,c_setting);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_set_default_size(VALUE self,VALUE width,VALUE height){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gint c_width;
  if (TYPE(width) == T_FIXNUM)
    c_width=FIX2INT(width);
  else if(TYPE(TYPE(width) == T_BIGNUM))
    c_width=NUM2INT(width);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gint c_height;
  if (TYPE(height) == T_FIXNUM)
    c_height=FIX2INT(height);
  else if(TYPE(TYPE(height) == T_BIGNUM))
    c_height=NUM2INT(height);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gtk_window_set_default_size(window,c_width,c_height);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_default_size(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gint local_c_width;
  gint * c_width = &local_c_width;
  gint local_c_height;
  gint * c_height = &local_c_height;
  gtk_window_get_default_size(window,c_width,c_height);
  VALUE r_ret= rb_ary_new();
  VALUE width = INT2NUM((int) local_c_width);

  rb_ary_push(r_ret, width);
  VALUE height = INT2NUM((int) local_c_height);

  rb_ary_push(r_ret, height);
  return r_ret;

}
static VALUE rtortosa_window_resize(VALUE self,VALUE width,VALUE height){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gint c_width;
  if (TYPE(width) == T_FIXNUM)
    c_width=FIX2INT(width);
  else if(TYPE(TYPE(width) == T_BIGNUM))
    c_width=NUM2INT(width);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gint c_height;
  if (TYPE(height) == T_FIXNUM)
    c_height=FIX2INT(height);
  else if(TYPE(TYPE(height) == T_BIGNUM))
    c_height=NUM2INT(height);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gtk_window_resize(window,c_width,c_height);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_size(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gint local_c_width;
  gint * c_width = &local_c_width;
  gint local_c_height;
  gint * c_height = &local_c_height;
  gtk_window_get_size(window,c_width,c_height);
  VALUE r_ret= rb_ary_new();
  VALUE width = INT2NUM((int) local_c_width);

  rb_ary_push(r_ret, width);
  VALUE height = INT2NUM((int) local_c_height);

  rb_ary_push(r_ret, height);
  return r_ret;

}
static VALUE rtortosa_window_move(VALUE self,VALUE x,VALUE y){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gint c_x;
  if (TYPE(x) == T_FIXNUM)
    c_x=FIX2INT(x);
  else if(TYPE(TYPE(x) == T_BIGNUM))
    c_x=NUM2INT(x);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gint c_y;
  if (TYPE(y) == T_FIXNUM)
    c_y=FIX2INT(y);
  else if(TYPE(TYPE(y) == T_BIGNUM))
    c_y=NUM2INT(y);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gtk_window_move(window,c_x,c_y);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_get_position(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gint local_c_root_x;
  gint * c_root_x = &local_c_root_x;
  gint local_c_root_y;
  gint * c_root_y = &local_c_root_y;
  gtk_window_get_position(window,c_root_x,c_root_y);
  VALUE r_ret= rb_ary_new();
  VALUE root_x = INT2NUM((int) local_c_root_x);

  rb_ary_push(r_ret, root_x);
  VALUE root_y = INT2NUM((int) local_c_root_y);

  rb_ary_push(r_ret, root_y);
  return r_ret;

}
static VALUE rtortosa_window_parse_geometry(VALUE self,VALUE geometry){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  if(TYPE(geometry) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_geometry=RSTRING_PTR(geometry);
  gboolean c_ret =gtk_window_parse_geometry(window,c_geometry);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_default_geometry(VALUE self,VALUE width,VALUE height){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gint c_width;
  if (TYPE(width) == T_FIXNUM)
    c_width=FIX2INT(width);
  else if(TYPE(TYPE(width) == T_BIGNUM))
    c_width=NUM2INT(width);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gint c_height;
  if (TYPE(height) == T_FIXNUM)
    c_height=FIX2INT(height);
  else if(TYPE(TYPE(height) == T_BIGNUM))
    c_height=NUM2INT(height);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gtk_window_set_default_geometry(window,c_width,c_height);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_resize_to_geometry(VALUE self,VALUE width,VALUE height){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gint c_width;
  if (TYPE(width) == T_FIXNUM)
    c_width=FIX2INT(width);
  else if(TYPE(TYPE(width) == T_BIGNUM))
    c_width=NUM2INT(width);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gint c_height;
  if (TYPE(height) == T_FIXNUM)
    c_height=FIX2INT(height);
  else if(TYPE(TYPE(height) == T_BIGNUM))
    c_height=NUM2INT(height);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gtk_window_resize_to_geometry(window,c_width,c_height);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_window_has_group(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_has_group(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_is_maximized(VALUE self){
  window_t *w;
  Data_Get_Struct(self, window_t,w);
  GtkWindow * window = GTK_WINDOW(w->widget);
  gboolean c_ret =gtk_window_is_maximized(window);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_window_set_interactive_debugging(VALUE enable){
  gboolean c_enable= (enable == Qtrue) ? TRUE : FALSE;
  gtk_window_set_interactive_debugging(c_enable);
 VALUE r_ret= Qnil;
  return r_ret;

}
VALUE generate_window_ruby_class_under(VALUE module, VALUE superclass) {
  VALUE c_window = rb_define_class_under(module, "Window", superclass);
  rb_define_alloc_func(c_window, c_window_struct_alloc);
//  return c_widget;
//}
  rb_define_method(c_window,
                                        "set_title",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_title),
                                        1);
  rb_define_method(c_window,
                                        "get_title",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_title),
                                        0);
  rb_define_method(c_window,
                                        "set_wmclass",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_wmclass),
                                        2);
  rb_define_method(c_window,
                                        "set_role",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_role),
                                        1);
  rb_define_method(c_window,
                                        "set_startup_id",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_startup_id),
                                        1);
  rb_define_method(c_window,
                                        "get_role",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_role),
                                        0);
  rb_define_method(c_window,
                                        "activate_focus",
                                        RUBY_METHOD_FUNC(rtortosa_window_activate_focus),
                                        0);
  rb_define_method(c_window,
                                        "activate_default",
                                        RUBY_METHOD_FUNC(rtortosa_window_activate_default),
                                        0);
  rb_define_method(c_window,
                                        "get_type_hint",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_type_hint),
                                        0);
  rb_define_method(c_window,
                                        "set_skip_taskbar_hint",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_skip_taskbar_hint),
                                        1);
  rb_define_method(c_window,
                                        "get_skip_taskbar_hint",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_skip_taskbar_hint),
                                        0);
  rb_define_method(c_window,
                                        "set_skip_pager_hint",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_skip_pager_hint),
                                        1);
  rb_define_method(c_window,
                                        "get_skip_pager_hint",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_skip_pager_hint),
                                        0);
  rb_define_method(c_window,
                                        "set_urgency_hint",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_urgency_hint),
                                        1);
  rb_define_method(c_window,
                                        "get_urgency_hint",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_urgency_hint),
                                        0);
  rb_define_method(c_window,
                                        "set_accept_focus",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_accept_focus),
                                        1);
  rb_define_method(c_window,
                                        "get_accept_focus",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_accept_focus),
                                        0);
  rb_define_method(c_window,
                                        "set_focus_on_map",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_focus_on_map),
                                        1);
  rb_define_method(c_window,
                                        "get_focus_on_map",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_focus_on_map),
                                        0);
  rb_define_method(c_window,
                                        "set_destroy_with_parent",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_destroy_with_parent),
                                        1);
  rb_define_method(c_window,
                                        "get_destroy_with_parent",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_destroy_with_parent),
                                        0);
  rb_define_method(c_window,
                                        "set_hide_titlebar_when_maximized",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_hide_titlebar_when_maximized),
                                        1);
  rb_define_method(c_window,
                                        "get_hide_titlebar_when_maximized",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_hide_titlebar_when_maximized),
                                        0);
  rb_define_method(c_window,
                                        "set_mnemonics_visible",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_mnemonics_visible),
                                        1);
  rb_define_method(c_window,
                                        "get_mnemonics_visible",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_mnemonics_visible),
                                        0);
  rb_define_method(c_window,
                                        "set_focus_visible",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_focus_visible),
                                        1);
  rb_define_method(c_window,
                                        "get_focus_visible",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_focus_visible),
                                        0);
  rb_define_method(c_window,
                                        "set_resizable",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_resizable),
                                        1);
  rb_define_method(c_window,
                                        "get_resizable",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_resizable),
                                        0);
  rb_define_method(c_window,
                                        "is_active",
                                        RUBY_METHOD_FUNC(rtortosa_window_is_active),
                                        0);
  rb_define_method(c_window,
                                        "has_toplevel_focus",
                                        RUBY_METHOD_FUNC(rtortosa_window_has_toplevel_focus),
                                        0);
  rb_define_method(c_window,
                                        "set_decorated",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_decorated),
                                        1);
  rb_define_method(c_window,
                                        "get_decorated",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_decorated),
                                        0);
  rb_define_method(c_window,
                                        "set_deletable",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_deletable),
                                        1);
  rb_define_method(c_window,
                                        "get_deletable",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_deletable),
                                        0);
  rb_define_method(c_window,
                                        "set_icon_name",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_icon_name),
                                        1);
  rb_define_method(c_window,
                                        "get_icon_name",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_icon_name),
                                        0);
  rb_define_method(c_window,
                                        "set_default_icon_name",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_default_icon_name),
                                        1);
  rb_define_method(c_window,
                                        "get_default_icon_name",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_default_icon_name),
                                        0);
  rb_define_method(c_window,
                                        "set_auto_startup_notification",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_auto_startup_notification),
                                        1);
  rb_define_method(c_window,
                                        "set_modal",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_modal),
                                        1);
  rb_define_method(c_window,
                                        "get_modal",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_modal),
                                        0);
  rb_define_method(c_window,
                                        "set_has_user_ref_count",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_has_user_ref_count),
                                        1);
  rb_define_method(c_window,
                                        "present",
                                        RUBY_METHOD_FUNC(rtortosa_window_present),
                                        0);
  rb_define_method(c_window,
                                        "iconify",
                                        RUBY_METHOD_FUNC(rtortosa_window_iconify),
                                        0);
  rb_define_method(c_window,
                                        "deiconify",
                                        RUBY_METHOD_FUNC(rtortosa_window_deiconify),
                                        0);
  rb_define_method(c_window,
                                        "stick",
                                        RUBY_METHOD_FUNC(rtortosa_window_stick),
                                        0);
  rb_define_method(c_window,
                                        "unstick",
                                        RUBY_METHOD_FUNC(rtortosa_window_unstick),
                                        0);
  rb_define_method(c_window,
                                        "maximize",
                                        RUBY_METHOD_FUNC(rtortosa_window_maximize),
                                        0);
  rb_define_method(c_window,
                                        "unmaximize",
                                        RUBY_METHOD_FUNC(rtortosa_window_unmaximize),
                                        0);
  rb_define_method(c_window,
                                        "fullscreen",
                                        RUBY_METHOD_FUNC(rtortosa_window_fullscreen),
                                        0);
  rb_define_method(c_window,
                                        "unfullscreen",
                                        RUBY_METHOD_FUNC(rtortosa_window_unfullscreen),
                                        0);
  rb_define_method(c_window,
                                        "close",
                                        RUBY_METHOD_FUNC(rtortosa_window_close),
                                        0);
  rb_define_method(c_window,
                                        "set_keep_above",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_keep_above),
                                        1);
  rb_define_method(c_window,
                                        "set_keep_below",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_keep_below),
                                        1);
  rb_define_method(c_window,
                                        "set_default_size",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_default_size),
                                        2);
  rb_define_method(c_window,
                                        "get_default_size",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_default_size),
                                        0);
  rb_define_method(c_window,
                                        "resize",
                                        RUBY_METHOD_FUNC(rtortosa_window_resize),
                                        2);
  rb_define_method(c_window,
                                        "get_size",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_size),
                                        0);
  rb_define_method(c_window,
                                        "move",
                                        RUBY_METHOD_FUNC(rtortosa_window_move),
                                        2);
  rb_define_method(c_window,
                                        "get_position",
                                        RUBY_METHOD_FUNC(rtortosa_window_get_position),
                                        0);
  rb_define_method(c_window,
                                        "parse_geometry",
                                        RUBY_METHOD_FUNC(rtortosa_window_parse_geometry),
                                        1);
  rb_define_method(c_window,
                                        "set_default_geometry",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_default_geometry),
                                        2);
  rb_define_method(c_window,
                                        "resize_to_geometry",
                                        RUBY_METHOD_FUNC(rtortosa_window_resize_to_geometry),
                                        2);
  rb_define_method(c_window,
                                        "has_group",
                                        RUBY_METHOD_FUNC(rtortosa_window_has_group),
                                        0);
  rb_define_method(c_window,
                                        "is_maximized",
                                        RUBY_METHOD_FUNC(rtortosa_window_is_maximized),
                                        0);
  rb_define_method(c_window,
                                        "set_interactive_debugging",
                                        RUBY_METHOD_FUNC(rtortosa_window_set_interactive_debugging),
                                        1);
  return c_window;
}
