/*notebook ruby class*/
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
/*static VALUE c_notebook_initialize(VALUE self, VALUE command)
{
}*/
static VALUE rtortosa_widget_destroy(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_destroy(widget);
  return Qnil;
}
static VALUE rtortosa_widget_destroyed(VALUE self,VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_destroyed(widget,c_widget_pointer);
  return Qnil;
}
static VALUE rtortosa_widget_unparent(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_unparent(widget);
  return Qnil;
}
static VALUE rtortosa_widget_show(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_show(widget);
  return Qnil;
}
static VALUE rtortosa_widget_hide(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_hide(widget);
  return Qnil;
}
static VALUE rtortosa_widget_show_now(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_show_now(widget);
  return Qnil;
}
static VALUE rtortosa_widget_show_all(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_show_all(widget);
  return Qnil;
}
static VALUE rtortosa_widget_set_no_show_all(VALUE self,VALUE no_show_all){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_no_show_all= (no_show_all == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_no_show_all(widget,c_no_show_all);
  return Qnil;
}
static VALUE rtortosa_widget_get_no_show_all(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_no_show_all(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_map(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_map(widget);
  return Qnil;
}
static VALUE rtortosa_widget_unmap(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_unmap(widget);
  return Qnil;
}
static VALUE rtortosa_widget_realize(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_realize(widget);
  return Qnil;
}
static VALUE rtortosa_widget_unrealize(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_unrealize(widget);
  return Qnil;
}
static VALUE rtortosa_widget_queue_draw(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_queue_draw(widget);
  return Qnil;
}
static VALUE rtortosa_widget_queue_resize(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_queue_resize(widget);
  return Qnil;
}
static VALUE rtortosa_widget_queue_resize_no_redraw(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_queue_resize_no_redraw(widget);
  return Qnil;
}
static VALUE rtortosa_widget_get_preferred_width(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint * c_minimum_width;
  if (TYPE(minimum_width) == T_FIXNUM)
    c_minimum_width=FIX2INT(minimum_width);
  else if(TYPE(TYPE(minimum_width) == T_BIGNUM))
    c_minimum_width=NUM2INT(minimum_width);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gint * c_natural_width;
  if (TYPE(natural_width) == T_FIXNUM)
    c_natural_width=FIX2INT(natural_width);
  else if(TYPE(TYPE(natural_width) == T_BIGNUM))
    c_natural_width=NUM2INT(natural_width);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gtk_widget_get_preferred_width(widget,c_minimum_width,c_natural_width);
  VALUE ret= rb_ary_new();
  rb_ary_push(ret, minimum_width);
  rb_ary_push(ret, natural_width);
  return ret;

}
static VALUE rtortosa_widget_get_preferred_height(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint * c_minimum_height;
  if (TYPE(minimum_height) == T_FIXNUM)
    c_minimum_height=FIX2INT(minimum_height);
  else if(TYPE(TYPE(minimum_height) == T_BIGNUM))
    c_minimum_height=NUM2INT(minimum_height);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gint * c_natural_height;
  if (TYPE(natural_height) == T_FIXNUM)
    c_natural_height=FIX2INT(natural_height);
  else if(TYPE(TYPE(natural_height) == T_BIGNUM))
    c_natural_height=NUM2INT(natural_height);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gtk_widget_get_preferred_height(widget,c_minimum_height,c_natural_height);
  VALUE ret= rb_ary_new();
  rb_ary_push(ret, minimum_height);
  rb_ary_push(ret, natural_height);
  return ret;

}
static VALUE rtortosa_widget_mnemonic_activate(VALUE self,VALUE group_cycling){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_group_cycling= (group_cycling == Qtrue) ? TRUE : FALSE;
  gboolean ret =gtk_widget_mnemonic_activate(widget,c_group_cycling);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_activate(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_activate(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_freeze_child_notify(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_freeze_child_notify(widget);
  return Qnil;
}
static VALUE rtortosa_widget_child_notify(VALUE self,VALUE child_property){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if(TYPE(child_property) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_child_property=RSTRING_PTR(child_property);
  gtk_widget_child_notify(widget,c_child_property);
  return Qnil;
}
static VALUE rtortosa_widget_thaw_child_notify(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_thaw_child_notify(widget);
  return Qnil;
}
static VALUE rtortosa_widget_set_can_focus(VALUE self,VALUE can_focus){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_can_focus= (can_focus == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_can_focus(widget,c_can_focus);
  return Qnil;
}
static VALUE rtortosa_widget_get_can_focus(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_can_focus(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_has_focus(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_has_focus(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_is_focus(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_is_focus(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_has_visible_focus(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_has_visible_focus(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_grab_focus(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_grab_focus(widget);
  return Qnil;
}
static VALUE rtortosa_widget_set_can_default(VALUE self,VALUE can_default){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_can_default= (can_default == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_can_default(widget,c_can_default);
  return Qnil;
}
static VALUE rtortosa_widget_get_can_default(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_can_default(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_has_default(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_has_default(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_grab_default(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_grab_default(widget);
  return Qnil;
}
static VALUE rtortosa_widget_set_receives_default(VALUE self,VALUE receives_default){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_receives_default= (receives_default == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_receives_default(widget,c_receives_default);
  return Qnil;
}
static VALUE rtortosa_widget_get_receives_default(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_receives_default(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_has_grab(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_has_grab(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_name(VALUE self,VALUE name){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if(TYPE(name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_name=RSTRING_PTR(name);
  gtk_widget_set_name(widget,c_name);
  return Qnil;
}
static VALUE rtortosa_widget_get_name(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  const gchar * ret =gtk_widget_get_name(widget);
  return rb_str_new2(ret);
}
static VALUE rtortosa_widget_set_sensitive(VALUE self,VALUE sensitive){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_sensitive= (sensitive == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_sensitive(widget,c_sensitive);
  return Qnil;
}
static VALUE rtortosa_widget_get_sensitive(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_sensitive(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_is_sensitive(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_is_sensitive(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_visible(VALUE self,VALUE visible){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_visible= (visible == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_visible(widget,c_visible);
  return Qnil;
}
static VALUE rtortosa_widget_get_visible(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_visible(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_is_visible(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_is_visible(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_has_window(VALUE self,VALUE has_window){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_has_window= (has_window == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_has_window(widget,c_has_window);
  return Qnil;
}
static VALUE rtortosa_widget_get_has_window(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_has_window(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_is_toplevel(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_is_toplevel(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_is_drawable(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_is_drawable(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_realized(VALUE self,VALUE realized){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_realized= (realized == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_realized(widget,c_realized);
  return Qnil;
}
static VALUE rtortosa_widget_get_realized(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_realized(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_mapped(VALUE self,VALUE mapped){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_mapped= (mapped == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_mapped(widget,c_mapped);
  return Qnil;
}
static VALUE rtortosa_widget_get_mapped(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_mapped(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_app_paintable(VALUE self,VALUE app_paintable){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_app_paintable= (app_paintable == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_app_paintable(widget,c_app_paintable);
  return Qnil;
}
static VALUE rtortosa_widget_get_app_paintable(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_app_paintable(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_double_buffered(VALUE self,VALUE double_buffered){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_double_buffered= (double_buffered == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_double_buffered(widget,c_double_buffered);
  return Qnil;
}
static VALUE rtortosa_widget_get_double_buffered(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_double_buffered(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_redraw_on_allocate(VALUE self,VALUE redraw_on_allocate){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_redraw_on_allocate= (redraw_on_allocate == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_redraw_on_allocate(widget,c_redraw_on_allocate);
  return Qnil;
}
static VALUE rtortosa_widget_set_child_visible(VALUE self,VALUE is_visible){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_is_visible= (is_visible == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_child_visible(widget,c_is_visible);
  return Qnil;
}
static VALUE rtortosa_widget_get_child_visible(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_child_visible(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_get_allocated_width(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  int ret =gtk_widget_get_allocated_width(widget);
  return INT2FIX(ret);
}
static VALUE rtortosa_widget_get_allocated_height(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  int ret =gtk_widget_get_allocated_height(widget);
  return INT2FIX(ret);
}
static VALUE rtortosa_widget_get_allocated_baseline(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  int ret =gtk_widget_get_allocated_baseline(widget);
  return INT2FIX(ret);
}
static VALUE rtortosa_widget_error_bell(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_error_bell(widget);
  return Qnil;
}
static VALUE rtortosa_widget_get_size_request(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint * c_width;
  if (TYPE(width) == T_FIXNUM)
    c_width=FIX2INT(width);
  else if(TYPE(TYPE(width) == T_BIGNUM))
    c_width=NUM2INT(width);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gint * c_height;
  if (TYPE(height) == T_FIXNUM)
    c_height=FIX2INT(height);
  else if(TYPE(TYPE(height) == T_BIGNUM))
    c_height=NUM2INT(height);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gtk_widget_get_size_request(widget,c_width,c_height);
  VALUE ret= rb_ary_new();
  rb_ary_push(ret, width);
  rb_ary_push(ret, height);
  return ret;

}
static VALUE rtortosa_widget_set_opacity(VALUE self,VALUE opacity){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if ((TYPE(opacity) != T_FIXNUM) && (TYPE(opacity) != T_BIGNUM))
    rb_raise(rb_eTypeError, "invalid type for input");
  double c_opacity=NUM2DBL(opacity);
  gtk_widget_set_opacity(widget,c_opacity);
  return Qnil;
}
static VALUE rtortosa_widget_get_opacity(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  double ret =gtk_widget_get_opacity(widget);
  return DBL2NUM(ret);
}
static VALUE rtortosa_widget_has_screen(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_has_screen(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_get_scale_factor(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint ret =gtk_widget_get_scale_factor(widget);
  return INT2FIX(ret);
}
static VALUE rtortosa_widget_get_hexpand(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_hexpand(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_hexpand(VALUE self,VALUE expand){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_expand= (expand == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_hexpand(widget,c_expand);
  return Qnil;
}
static VALUE rtortosa_widget_get_hexpand_set(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_hexpand_set(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_hexpand_set(VALUE self,VALUE set){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_set= (set == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_hexpand_set(widget,c_set);
  return Qnil;
}
static VALUE rtortosa_widget_get_vexpand(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_vexpand(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_vexpand(VALUE self,VALUE expand){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_expand= (expand == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_vexpand(widget,c_expand);
  return Qnil;
}
static VALUE rtortosa_widget_get_vexpand_set(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_vexpand_set(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_vexpand_set(VALUE self,VALUE set){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_set= (set == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_vexpand_set(widget,c_set);
  return Qnil;
}
static VALUE rtortosa_widget_queue_compute_expand(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_queue_compute_expand(widget);
  return Qnil;
}
static VALUE rtortosa_widget_get_support_multidevice(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_support_multidevice(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_set_support_multidevice(VALUE self,VALUE support_multidevice){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_support_multidevice= (support_multidevice == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_support_multidevice(widget,c_support_multidevice);
  return Qnil;
}
static VALUE rtortosa_widget_get_margin_left(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint ret =gtk_widget_get_margin_left(widget);
  return INT2FIX(ret);
}
static VALUE rtortosa_widget_get_margin_right(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint ret =gtk_widget_get_margin_right(widget);
  return INT2FIX(ret);
}
static VALUE rtortosa_widget_get_margin_start(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint ret =gtk_widget_get_margin_start(widget);
  return INT2FIX(ret);
}
static VALUE rtortosa_widget_get_margin_end(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint ret =gtk_widget_get_margin_end(widget);
  return INT2FIX(ret);
}
static VALUE rtortosa_widget_get_margin_top(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint ret =gtk_widget_get_margin_top(widget);
  return INT2FIX(ret);
}
static VALUE rtortosa_widget_get_margin_bottom(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint ret =gtk_widget_get_margin_bottom(widget);
  return INT2FIX(ret);
}
static VALUE rtortosa_widget_get_events(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint ret =gtk_widget_get_events(widget);
  return INT2FIX(ret);
}
static VALUE rtortosa_widget_get_pointer(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gint * c_x;
  if (TYPE(x) == T_FIXNUM)
    c_x=FIX2INT(x);
  else if(TYPE(TYPE(x) == T_BIGNUM))
    c_x=NUM2INT(x);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gint * c_y;
  if (TYPE(y) == T_FIXNUM)
    c_y=FIX2INT(y);
  else if(TYPE(TYPE(y) == T_BIGNUM))
    c_y=NUM2INT(y);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gtk_widget_get_pointer(widget,c_x,c_y);
  VALUE ret= rb_ary_new();
  rb_ary_push(ret, x);
  rb_ary_push(ret, y);
  return ret;

}
static VALUE rtortosa_widget_is_ancestor(VALUE self,VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_is_ancestor(widget,widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_hide_on_delete(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_hide_on_delete(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_reset_style(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_reset_style(widget);
  return Qnil;
}
static VALUE rtortosa_widget_set_composite_name(VALUE self,VALUE name){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if(TYPE(name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_name=RSTRING_PTR(name);
  gtk_widget_set_composite_name(widget,c_name);
  return Qnil;
}
static VALUE rtortosa_widget_get_composite_name(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gchar * ret =gtk_widget_get_composite_name(widget);
  return rb_str_new2(ret);
}
static VALUE rtortosa_widget_push_composite_child(){
  gtk_widget_push_composite_child();
  return Qnil;
}
static VALUE rtortosa_widget_pop_composite_child(){
  gtk_widget_pop_composite_child();
  return Qnil;
}
static VALUE rtortosa_widget_style_get(VALUE self,VALUE first_property_name){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if(TYPE(first_property_name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_first_property_name=RSTRING_PTR(first_property_name);
  gtk_widget_style_get(widget,c_first_property_name);
  return Qnil;
}
static VALUE rtortosa_widget_is_composited(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_is_composited(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_add_mnemonic_label(VALUE self,VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_add_mnemonic_label(widget,widget);
  return Qnil;
}
static VALUE rtortosa_widget_remove_mnemonic_label(VALUE self,VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_remove_mnemonic_label(widget,widget);
  return Qnil;
}
static VALUE rtortosa_widget_trigger_tooltip_query(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_trigger_tooltip_query(widget);
  return Qnil;
}
static VALUE rtortosa_widget_set_tooltip_text(VALUE self,VALUE text){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if(TYPE(text) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_text=RSTRING_PTR(text);
  gtk_widget_set_tooltip_text(widget,c_text);
  return Qnil;
}
static VALUE rtortosa_widget_get_tooltip_text(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gchar * ret =gtk_widget_get_tooltip_text(widget);
  return rb_str_new2(ret);
}
static VALUE rtortosa_widget_set_tooltip_markup(VALUE self,VALUE markup){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  if(TYPE(markup) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_markup=RSTRING_PTR(markup);
  gtk_widget_set_tooltip_markup(widget,c_markup);
  return Qnil;
}
static VALUE rtortosa_widget_get_tooltip_markup(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gchar * ret =gtk_widget_get_tooltip_markup(widget);
  return rb_str_new2(ret);
}
static VALUE rtortosa_widget_set_has_tooltip(VALUE self,VALUE has_tooltip){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean c_has_tooltip= (has_tooltip == Qtrue) ? TRUE : FALSE;
  gtk_widget_set_has_tooltip(widget,c_has_tooltip);
  return Qnil;
}
static VALUE rtortosa_widget_get_has_tooltip(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_get_has_tooltip(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_in_destruction(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gboolean ret =gtk_widget_in_destruction(widget);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_widget_init_template(VALUE self){
  widget_t *w;
  Data_Get_Struct(self, widget_t,w);
  GtkWidget * widget = w->widget;
  gtk_widget_init_template(widget);
  return Qnil;
}
static VALUE rtortosa_widget_class_set_template_from_resource(VALUE resource_name){
  if(TYPE(resource_name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_resource_name=RSTRING_PTR(resource_name);
  gtk_widget_class_set_template_from_resource(c_widget_class,c_resource_name);
  return Qnil;
}
VALUE generate_widget_ruby_class_under(VALUE module) {
  VALUE c_widget = rb_define_class_under(module, "Widget", rb_cObject);
  return c_widget;
}
  rb_define_method(c_widget,
                                        "destroy",
                                        RUBY_METHOD_FUNC(rtortosa_widget_destroy),
                                        0);
  rb_define_method(c_widget,
                                        "destroyed",
                                        RUBY_METHOD_FUNC(rtortosa_widget_destroyed),
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
                                        2);
  rb_define_method(c_widget,
                                        "get_preferred_height",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_preferred_height),
                                        2);
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
                                        "set_double_buffered",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_double_buffered),
                                        1);
  rb_define_method(c_widget,
                                        "get_double_buffered",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_double_buffered),
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
                                        2);
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
                                        "get_margin_left",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_margin_left),
                                        0);
  rb_define_method(c_widget,
                                        "get_margin_right",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_margin_right),
                                        0);
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
                                        "get_pointer",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_pointer),
                                        2);
  rb_define_method(c_widget,
                                        "is_ancestor",
                                        RUBY_METHOD_FUNC(rtortosa_widget_is_ancestor),
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
                                        "set_composite_name",
                                        RUBY_METHOD_FUNC(rtortosa_widget_set_composite_name),
                                        1);
  rb_define_method(c_widget,
                                        "get_composite_name",
                                        RUBY_METHOD_FUNC(rtortosa_widget_get_composite_name),
                                        0);
  rb_define_method(c_widget,
                                        "push_composite_child",
                                        RUBY_METHOD_FUNC(rtortosa_widget_push_composite_child),
                                        0);
  rb_define_method(c_widget,
                                        "pop_composite_child",
                                        RUBY_METHOD_FUNC(rtortosa_widget_pop_composite_child),
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
                                        "add_mnemonic_label",
                                        RUBY_METHOD_FUNC(rtortosa_widget_add_mnemonic_label),
                                        0);
  rb_define_method(c_widget,
                                        "remove_mnemonic_label",
                                        RUBY_METHOD_FUNC(rtortosa_widget_remove_mnemonic_label),
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
  rb_define_method(c_widget,
                                        "init_template",
                                        RUBY_METHOD_FUNC(rtortosa_widget_init_template),
                                        0);
  rb_define_method(c_widget,
                                        "class_set_template_from_resource",
                                        RUBY_METHOD_FUNC(rtortosa_widget_class_set_template_from_resource),
                                        1);
}
