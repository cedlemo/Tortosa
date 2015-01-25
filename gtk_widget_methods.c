 /*widget ruby class*/
#include "gtk_widget_methods.h"

static void c_widget_struct_free(widget_t *c)
{
  if(c)
  {
    ruby_xfree(c);
  }
}
static VALUE c_widget_struct_alloc( VALUE klass)
{
  return Data_Wrap_Struct(klass, NULL, c_widget_struct_free, ruby_xmalloc(sizeof(widget_t)));
}
/*static VALUE c_widget_initialize(VALUE self)
{
}*/
static VALUE rtortosa_widget_destroy(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_destroy(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_unparent(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_unparent(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_show(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_show(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_hide(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_hide(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_show_now(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_show_now(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_show_all(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_show_all(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_set_no_show_all(VALUE self,VALUE no_show_all){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_no_show_all= (no_show_all == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_no_show_all(widget,c_no_show_all);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_no_show_all(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_no_show_all(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_map(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_map(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_unmap(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_unmap(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_realize(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_realize(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_unrealize(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_unrealize(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_queue_draw(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_queue_draw(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_queue_resize(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_queue_resize(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_queue_resize_no_redraw(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_queue_resize_no_redraw(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_preferred_width(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint local_c_minimum_width;
  gint * c_minimum_width = &local_c_minimum_width;
  gint local_c_natural_width;
  gint * c_natural_width = &local_c_natural_width;
  gtk_widget_get_preferred_width(widget,c_minimum_width,c_natural_width);
  VALUE r_ret= rb_ary_new();
  VALUE minimum_width = INT2NUM((int) local_c_minimum_width);

  rb_ary_push(r_ret, minimum_width);
  VALUE natural_width = INT2NUM((int) local_c_natural_width);

  rb_ary_push(r_ret, natural_width);
  return r_ret;

}
static VALUE rtortosa_widget_get_preferred_height(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint local_c_minimum_height;
  gint * c_minimum_height = &local_c_minimum_height;
  gint local_c_natural_height;
  gint * c_natural_height = &local_c_natural_height;
  gtk_widget_get_preferred_height(widget,c_minimum_height,c_natural_height);
  VALUE r_ret= rb_ary_new();
  VALUE minimum_height = INT2NUM((int) local_c_minimum_height);

  rb_ary_push(r_ret, minimum_height);
  VALUE natural_height = INT2NUM((int) local_c_natural_height);

  rb_ary_push(r_ret, natural_height);
  return r_ret;

}
static VALUE rtortosa_widget_mnemonic_activate(VALUE self,VALUE group_cycling){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_group_cycling= (group_cycling == Qtrue) ? TRUE : FALSE;
  gboolean c_ret =gtk_widget_mnemonic_activate(widget,c_group_cycling);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_activate(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_activate(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_freeze_child_notify(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_freeze_child_notify(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_child_notify(VALUE self,VALUE child_property){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if(TYPE(child_property) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_child_property=RSTRING_PTR(child_property);
  gtk_widget_child_notify(widget,c_child_property);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_thaw_child_notify(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_thaw_child_notify(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_set_can_focus(VALUE self,VALUE can_focus){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_can_focus= (can_focus == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_can_focus(widget,c_can_focus);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_can_focus(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_can_focus(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_has_focus(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_has_focus(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_is_focus(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_is_focus(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_has_visible_focus(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_has_visible_focus(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_grab_focus(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_grab_focus(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_set_can_default(VALUE self,VALUE can_default){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_can_default= (can_default == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_can_default(widget,c_can_default);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_can_default(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_can_default(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_has_default(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_has_default(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_grab_default(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_grab_default(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_set_receives_default(VALUE self,VALUE receives_default){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_receives_default= (receives_default == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_receives_default(widget,c_receives_default);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_receives_default(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_receives_default(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_has_grab(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_has_grab(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_set_name(VALUE self,VALUE name){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if(TYPE(name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_name=RSTRING_PTR(name);
  gtk_widget_set_name(widget,c_name);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_name(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  const gchar * c_ret =gtk_widget_get_name(widget);
  VALUE r_ret = rb_str_new2(c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_set_sensitive(VALUE self,VALUE sensitive){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_sensitive= (sensitive == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_sensitive(widget,c_sensitive);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_sensitive(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_sensitive(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_is_sensitive(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_is_sensitive(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_set_visible(VALUE self,VALUE visible){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_visible= (visible == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_visible(widget,c_visible);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_visible(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_visible(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_is_visible(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_is_visible(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_set_has_window(VALUE self,VALUE has_window){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_has_window= (has_window == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_has_window(widget,c_has_window);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_has_window(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_has_window(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_is_toplevel(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_is_toplevel(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_is_drawable(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_is_drawable(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_set_realized(VALUE self,VALUE realized){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_realized= (realized == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_realized(widget,c_realized);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_realized(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_realized(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_set_mapped(VALUE self,VALUE mapped){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_mapped= (mapped == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_mapped(widget,c_mapped);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_mapped(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_mapped(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_set_app_paintable(VALUE self,VALUE app_paintable){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_app_paintable= (app_paintable == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_app_paintable(widget,c_app_paintable);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_app_paintable(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_app_paintable(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_set_redraw_on_allocate(VALUE self,VALUE redraw_on_allocate){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_redraw_on_allocate= (redraw_on_allocate == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_redraw_on_allocate(widget,c_redraw_on_allocate);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_set_child_visible(VALUE self,VALUE is_visible){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_is_visible= (is_visible == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_child_visible(widget,c_is_visible);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_child_visible(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_child_visible(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_get_allocated_width(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  int c_ret =gtk_widget_get_allocated_width(widget);
  VALUE r_ret = INT2NUM((int) c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_get_allocated_height(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  int c_ret =gtk_widget_get_allocated_height(widget);
  VALUE r_ret = INT2NUM((int) c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_get_allocated_baseline(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  int c_ret =gtk_widget_get_allocated_baseline(widget);
  VALUE r_ret = INT2NUM((int) c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_error_bell(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_error_bell(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_size_request(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint local_c_width;
  gint * c_width = &local_c_width;
  gint local_c_height;
  gint * c_height = &local_c_height;
  gtk_widget_get_size_request(widget,c_width,c_height);
  VALUE r_ret= rb_ary_new();
  VALUE width = INT2NUM((int) local_c_width);

  rb_ary_push(r_ret, width);
  VALUE height = INT2NUM((int) local_c_height);

  rb_ary_push(r_ret, height);
  return r_ret;

}
static VALUE rtortosa_widget_set_opacity(VALUE self,VALUE opacity){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if ((TYPE(opacity) != T_FIXNUM) && (TYPE(opacity) != T_BIGNUM))
    rb_raise(rb_eTypeError, "invalid type for input");
  double c_opacity=NUM2DBL(opacity);
  gtk_widget_set_opacity(widget,c_opacity);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_opacity(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  double c_ret =gtk_widget_get_opacity(widget);
  VALUE r_ret = DBL2NUM(c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_has_screen(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_has_screen(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_get_scale_factor(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint c_ret =gtk_widget_get_scale_factor(widget);
  VALUE r_ret = INT2NUM((int) c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_get_hexpand(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_hexpand(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_set_hexpand(VALUE self,VALUE expand){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_expand= (expand == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_hexpand(widget,c_expand);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_hexpand_set(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_hexpand_set(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_set_hexpand_set(VALUE self,VALUE set){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_set= (set == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_hexpand_set(widget,c_set);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_vexpand(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_vexpand(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_set_vexpand(VALUE self,VALUE expand){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_expand= (expand == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_vexpand(widget,c_expand);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_vexpand_set(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_vexpand_set(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_set_vexpand_set(VALUE self,VALUE set){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_set= (set == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_vexpand_set(widget,c_set);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_queue_compute_expand(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_queue_compute_expand(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_support_multidevice(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_support_multidevice(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_set_support_multidevice(VALUE self,VALUE support_multidevice){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_support_multidevice= (support_multidevice == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_support_multidevice(widget,c_support_multidevice);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_margin_start(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint c_ret =gtk_widget_get_margin_start(widget);
  VALUE r_ret = INT2NUM((int) c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_get_margin_end(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint c_ret =gtk_widget_get_margin_end(widget);
  VALUE r_ret = INT2NUM((int) c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_get_margin_top(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint c_ret =gtk_widget_get_margin_top(widget);
  VALUE r_ret = INT2NUM((int) c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_get_margin_bottom(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint c_ret =gtk_widget_get_margin_bottom(widget);
  VALUE r_ret = INT2NUM((int) c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_get_events(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint c_ret =gtk_widget_get_events(widget);
  VALUE r_ret = INT2NUM((int) c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_hide_on_delete(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_hide_on_delete(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_reset_style(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_reset_style(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_style_get(VALUE self,VALUE first_property_name){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if(TYPE(first_property_name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_first_property_name=RSTRING_PTR(first_property_name);
  gtk_widget_style_get(widget,c_first_property_name);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_is_composited(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_is_composited(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_trigger_tooltip_query(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_trigger_tooltip_query(widget);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_set_tooltip_text(VALUE self,VALUE text){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if(TYPE(text) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_text=RSTRING_PTR(text);
  gtk_widget_set_tooltip_text(widget,c_text);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_tooltip_text(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gchar * c_ret =gtk_widget_get_tooltip_text(widget);
  VALUE r_ret = rb_str_new2(c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_set_tooltip_markup(VALUE self,VALUE markup){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if(TYPE(markup) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_markup=RSTRING_PTR(markup);
  gtk_widget_set_tooltip_markup(widget,c_markup);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_tooltip_markup(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gchar * c_ret =gtk_widget_get_tooltip_markup(widget);
  VALUE r_ret = rb_str_new2(c_ret);

  return r_ret;

}
static VALUE rtortosa_widget_set_has_tooltip(VALUE self,VALUE has_tooltip){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_has_tooltip= (has_tooltip == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_has_tooltip(widget,c_has_tooltip);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_widget_get_has_tooltip(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_get_has_tooltip(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_widget_in_destruction(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_ret =gtk_widget_in_destruction(widget);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
VALUE generate_widget_ruby_class_under(VALUE module, VALUE superclass) {
  VALUE c_widget = rb_define_class_under(module, "Widget", superclass);
//  return c_widget;
//}
  rb_define_method(c_widget,
                                        "destroy",
                                        RUBY_METHOD_FUNC(rtortosa_widget_destroy),
                                        0);
  rb_define_method(c_widget,
                                        "unparent",
                                        RUBY_METHOD_FUNC(rtortosa_widget_unparent),
                                        0);
  rb_define_method(c_widget,
                                        "show",
                                        RUBY_METHOD_FUNC(rtortosa_widget_show),
                                        0);
  rb_define_method(c_widget,
                                        "hide",
                                        RUBY_METHOD_FUNC(rtortosa_widget_hide),
                                        0);
  rb_define_method(c_widget,
                                        "show_now",
                                        RUBY_METHOD_FUNC(rtortosa_widget_show_now),
                                        0);
  rb_define_method(c_widget,
                                        "show_all",
                                        RUBY_METHOD_FUNC(rtortosa_widget_show_all),
                                        0);
  rb_define_method(c_widget,
                                        "set_no_show_all",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_no_show_all),
                                        1);
  rb_define_method(c_widget,
                                        "get_no_show_all",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_no_show_all),
                                        0);
  rb_define_method(c_widget,
                                        "map",
                                        RUBY_METHOD_FUNC(rtortosa_widget_map),
                                        0);
  rb_define_method(c_widget,
                                        "unmap",
                                        RUBY_METHOD_FUNC(rtortosa_widget_unmap),
                                        0);
  rb_define_method(c_widget,
                                        "realize",
                                        RUBY_METHOD_FUNC(rtortosa_widget_realize),
                                        0);
  rb_define_method(c_widget,
                                        "unrealize",
                                        RUBY_METHOD_FUNC(rtortosa_widget_unrealize),
                                        0);
  rb_define_method(c_widget,
                                        "queue_draw",
                                        RUBY_METHOD_FUNC(rtortosa_widget_queue_draw),
                                        0);
  rb_define_method(c_widget,
                                        "queue_resize",
                                        RUBY_METHOD_FUNC(rtortosa_widget_queue_resize),
                                        0);
  rb_define_method(c_widget,
                                        "queue_resize_no_redraw",
                                        RUBY_METHOD_FUNC(rtortosa_widget_queue_resize_no_redraw),
                                        0);
  rb_define_method(c_widget,
                                        "get_preferred_width",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_preferred_width),
                                        0);
  rb_define_method(c_widget,
                                        "get_preferred_height",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_preferred_height),
                                        0);
  rb_define_method(c_widget,
                                        "mnemonic_activate",
                                        RUBY_METHOD_FUNC(rtortosa_widget_mnemonic_activate),
                                        1);
  rb_define_method(c_widget,
                                        "activate",
                                        RUBY_METHOD_FUNC(rtortosa_widget_activate),
                                        0);
  rb_define_method(c_widget,
                                        "freeze_child_notify",
                                        RUBY_METHOD_FUNC(rtortosa_widget_freeze_child_notify),
                                        0);
  rb_define_method(c_widget,
                                        "child_notify",
                                        RUBY_METHOD_FUNC(rtortosa_widget_child_notify),
                                        1);
  rb_define_method(c_widget,
                                        "thaw_child_notify",
                                        RUBY_METHOD_FUNC(rtortosa_widget_thaw_child_notify),
                                        0);
  rb_define_method(c_widget,
                                        "set_can_focus",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_can_focus),
                                        1);
  rb_define_method(c_widget,
                                        "get_can_focus",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_can_focus),
                                        0);
  rb_define_method(c_widget,
                                        "has_focus",
                                        RUBY_METHOD_FUNC(rtortosa_widget_has_focus),
                                        0);
  rb_define_method(c_widget,
                                        "is_focus",
                                        RUBY_METHOD_FUNC(rtortosa_widget_is_focus),
                                        0);
  rb_define_method(c_widget,
                                        "has_visible_focus",
                                        RUBY_METHOD_FUNC(rtortosa_widget_has_visible_focus),
                                        0);
  rb_define_method(c_widget,
                                        "grab_focus",
                                        RUBY_METHOD_FUNC(rtortosa_widget_grab_focus),
                                        0);
  rb_define_method(c_widget,
                                        "set_can_default",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_can_default),
                                        1);
  rb_define_method(c_widget,
                                        "get_can_default",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_can_default),
                                        0);
  rb_define_method(c_widget,
                                        "has_default",
                                        RUBY_METHOD_FUNC(rtortosa_widget_has_default),
                                        0);
  rb_define_method(c_widget,
                                        "grab_default",
                                        RUBY_METHOD_FUNC(rtortosa_widget_grab_default),
                                        0);
  rb_define_method(c_widget,
                                        "set_receives_default",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_receives_default),
                                        1);
  rb_define_method(c_widget,
                                        "get_receives_default",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_receives_default),
                                        0);
  rb_define_method(c_widget,
                                        "has_grab",
                                        RUBY_METHOD_FUNC(rtortosa_widget_has_grab),
                                        0);
  rb_define_method(c_widget,
                                        "set_name",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_name),
                                        1);
  rb_define_method(c_widget,
                                        "get_name",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_name),
                                        0);
  rb_define_method(c_widget,
                                        "set_sensitive",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_sensitive),
                                        1);
  rb_define_method(c_widget,
                                        "get_sensitive",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_sensitive),
                                        0);
  rb_define_method(c_widget,
                                        "is_sensitive",
                                        RUBY_METHOD_FUNC(rtortosa_widget_is_sensitive),
                                        0);
  rb_define_method(c_widget,
                                        "set_visible",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_visible),
                                        1);
  rb_define_method(c_widget,
                                        "get_visible",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_visible),
                                        0);
  rb_define_method(c_widget,
                                        "is_visible",
                                        RUBY_METHOD_FUNC(rtortosa_widget_is_visible),
                                        0);
  rb_define_method(c_widget,
                                        "set_has_window",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_has_window),
                                        1);
  rb_define_method(c_widget,
                                        "get_has_window",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_has_window),
                                        0);
  rb_define_method(c_widget,
                                        "is_toplevel",
                                        RUBY_METHOD_FUNC(rtortosa_widget_is_toplevel),
                                        0);
  rb_define_method(c_widget,
                                        "is_drawable",
                                        RUBY_METHOD_FUNC(rtortosa_widget_is_drawable),
                                        0);
  rb_define_method(c_widget,
                                        "set_realized",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_realized),
                                        1);
  rb_define_method(c_widget,
                                        "get_realized",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_realized),
                                        0);
  rb_define_method(c_widget,
                                        "set_mapped",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_mapped),
                                        1);
  rb_define_method(c_widget,
                                        "get_mapped",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_mapped),
                                        0);
  rb_define_method(c_widget,
                                        "set_app_paintable",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_app_paintable),
                                        1);
  rb_define_method(c_widget,
                                        "get_app_paintable",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_app_paintable),
                                        0);
  rb_define_method(c_widget,
                                        "set_redraw_on_allocate",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_redraw_on_allocate),
                                        1);
  rb_define_method(c_widget,
                                        "set_child_visible",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_child_visible),
                                        1);
  rb_define_method(c_widget,
                                        "get_child_visible",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_child_visible),
                                        0);
  rb_define_method(c_widget,
                                        "get_allocated_width",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_allocated_width),
                                        0);
  rb_define_method(c_widget,
                                        "get_allocated_height",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_allocated_height),
                                        0);
  rb_define_method(c_widget,
                                        "get_allocated_baseline",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_allocated_baseline),
                                        0);
  rb_define_method(c_widget,
                                        "error_bell",
                                        RUBY_METHOD_FUNC(rtortosa_widget_error_bell),
                                        0);
  rb_define_method(c_widget,
                                        "get_size_request",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_size_request),
                                        0);
  rb_define_method(c_widget,
                                        "set_opacity",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_opacity),
                                        1);
  rb_define_method(c_widget,
                                        "get_opacity",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_opacity),
                                        0);
  rb_define_method(c_widget,
                                        "has_screen",
                                        RUBY_METHOD_FUNC(rtortosa_widget_has_screen),
                                        0);
  rb_define_method(c_widget,
                                        "get_scale_factor",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_scale_factor),
                                        0);
  rb_define_method(c_widget,
                                        "get_hexpand",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_hexpand),
                                        0);
  rb_define_method(c_widget,
                                        "set_hexpand",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_hexpand),
                                        1);
  rb_define_method(c_widget,
                                        "get_hexpand_set",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_hexpand_set),
                                        0);
  rb_define_method(c_widget,
                                        "set_hexpand_set",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_hexpand_set),
                                        1);
  rb_define_method(c_widget,
                                        "get_vexpand",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_vexpand),
                                        0);
  rb_define_method(c_widget,
                                        "set_vexpand",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_vexpand),
                                        1);
  rb_define_method(c_widget,
                                        "get_vexpand_set",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_vexpand_set),
                                        0);
  rb_define_method(c_widget,
                                        "set_vexpand_set",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_vexpand_set),
                                        1);
  rb_define_method(c_widget,
                                        "queue_compute_expand",
                                        RUBY_METHOD_FUNC(rtortosa_widget_queue_compute_expand),
                                        0);
  rb_define_method(c_widget,
                                        "get_support_multidevice",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_support_multidevice),
                                        0);
  rb_define_method(c_widget,
                                        "set_support_multidevice",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_support_multidevice),
                                        1);
  rb_define_method(c_widget,
                                        "get_margin_start",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_margin_start),
                                        0);
  rb_define_method(c_widget,
                                        "get_margin_end",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_margin_end),
                                        0);
  rb_define_method(c_widget,
                                        "get_margin_top",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_margin_top),
                                        0);
  rb_define_method(c_widget,
                                        "get_margin_bottom",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_margin_bottom),
                                        0);
  rb_define_method(c_widget,
                                        "get_events",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_events),
                                        0);
  rb_define_method(c_widget,
                                        "hide_on_delete",
                                        RUBY_METHOD_FUNC(rtortosa_widget_hide_on_delete),
                                        0);
  rb_define_method(c_widget,
                                        "reset_style",
                                        RUBY_METHOD_FUNC(rtortosa_widget_reset_style),
                                        0);
  rb_define_method(c_widget,
                                        "style_get",
                                        RUBY_METHOD_FUNC(rtortosa_widget_style_get),
                                        1);
  rb_define_method(c_widget,
                                        "is_composited",
                                        RUBY_METHOD_FUNC(rtortosa_widget_is_composited),
                                        0);
  rb_define_method(c_widget,
                                        "trigger_tooltip_query",
                                        RUBY_METHOD_FUNC(rtortosa_widget_trigger_tooltip_query),
                                        0);
  rb_define_method(c_widget,
                                        "set_tooltip_text",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_tooltip_text),
                                        1);
  rb_define_method(c_widget,
                                        "get_tooltip_text",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_tooltip_text),
                                        0);
  rb_define_method(c_widget,
                                        "set_tooltip_markup",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_tooltip_markup),
                                        1);
  rb_define_method(c_widget,
                                        "get_tooltip_markup",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_tooltip_markup),
                                        0);
  rb_define_method(c_widget,
                                        "set_has_tooltip",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_has_tooltip),
                                        1);
  rb_define_method(c_widget,
                                        "get_has_tooltip",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_has_tooltip),
                                        0);
  rb_define_method(c_widget,
                                        "in_destruction",
                                        RUBY_METHOD_FUNC(rtortosa_widget_in_destruction),
                                        0);
  return c_widget;
}
