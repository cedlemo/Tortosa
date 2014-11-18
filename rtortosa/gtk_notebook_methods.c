#include "gtk_notebook_methods.h"
static VALUE rtortosa_notebook_remove_page(VALUE self, VALUE page_num){
  if (TYPE(page_num) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  gint r_page_num=FIX2INT(page_num);
  gtk_notebook_remove_page(GTK_NOTEBOOK(backbone.window.notebook),r_page_num);
  return Qnil;
}
static VALUE rtortosa_notebook_set_group_name(VALUE self, VALUE group_name){
  if(TYPE(group_name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * r_group_name=RSTRING_PTR(group_name);
  gtk_notebook_set_group_name(GTK_NOTEBOOK(backbone.window.notebook),r_group_name);
  return Qnil;
}
static VALUE rtortosa_notebook_get_group_name(VALUE self){
  const gchar * ret =gtk_notebook_get_group_name(GTK_NOTEBOOK(backbone.window.notebook));
  return rb_strnew2(ret);
}
static VALUE rtortosa_notebook_get_current_page(VALUE self){
  gint ret =gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone.window.notebook));
  return INT2FIX(ret);
}
static VALUE rtortosa_notebook_get_n_pages(VALUE self){
  gint ret =gtk_notebook_get_n_pages(GTK_NOTEBOOK(backbone.window.notebook));
  return INT2FIX(ret);
}
static VALUE rtortosa_notebook_set_current_page(VALUE self, VALUE page_num){
  if (TYPE(page_num) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  gint r_page_num=FIX2INT(page_num);
  gtk_notebook_set_current_page(GTK_NOTEBOOK(backbone.window.notebook),r_page_num);
  return Qnil;
}
static VALUE rtortosa_notebook_next_page(VALUE self){
  gtk_notebook_next_page(GTK_NOTEBOOK(backbone.window.notebook));
  return Qnil;
}
static VALUE rtortosa_notebook_prev_page(VALUE self){
  gtk_notebook_prev_page(GTK_NOTEBOOK(backbone.window.notebook));
  return Qnil;
}
static VALUE rtortosa_notebook_set_show_border(VALUE self, VALUE show_border){
  gboolean r_show_border= (show_border == Qtrue) ? TRUE : FALSE;
  gtk_notebook_set_show_border(GTK_NOTEBOOK(backbone.window.notebook),r_show_border);
  return Qnil;
}
static VALUE rtortosa_notebook_get_show_border(VALUE self){
  gboolean ret =gtk_notebook_get_show_border(GTK_NOTEBOOK(backbone.window.notebook));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_notebook_set_show_tabs(VALUE self, VALUE show_tabs){
  gboolean r_show_tabs= (show_tabs == Qtrue) ? TRUE : FALSE;
  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(backbone.window.notebook),r_show_tabs);
  return Qnil;
}
static VALUE rtortosa_notebook_get_show_tabs(VALUE self){
  gboolean ret =gtk_notebook_get_show_tabs(GTK_NOTEBOOK(backbone.window.notebook));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_notebook_set_scrollable(VALUE self, VALUE scrollable){
  gboolean r_scrollable= (scrollable == Qtrue) ? TRUE : FALSE;
  gtk_notebook_set_scrollable(GTK_NOTEBOOK(backbone.window.notebook),r_scrollable);
  return Qnil;
}
static VALUE rtortosa_notebook_get_scrollable(VALUE self){
  gboolean ret =gtk_notebook_get_scrollable(GTK_NOTEBOOK(backbone.window.notebook));
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_notebook_popup_enable(VALUE self){
  gtk_notebook_popup_enable(GTK_NOTEBOOK(backbone.window.notebook));
  return Qnil;
}
static VALUE rtortosa_notebook_popup_disable(VALUE self){
  gtk_notebook_popup_disable(GTK_NOTEBOOK(backbone.window.notebook));
  return Qnil;
}
void gtk_notebook_wrapper(VALUE module){
  rb_define_const(module, "POS_LEFT", INT2FIX(GTK_POS_LEFT) );
  rb_define_const(module, "POS_RIGHT", INT2FIX(GTK_POS_RIGHT) );
  rb_define_const(module, "POS_TOP", INT2FIX(GTK_POS_TOP) );
  rb_define_const(module, "POS_BOTTOM", INT2FIX(GTK_POS_BOTTOM));
  rb_define_module_function(module, 
                                        "notebook_remove_page", 
                                        rtortosa_notebook_remove_page,
                                        1);
  rb_define_module_function(module, 
                                        "notebook_set_group_name", 
                                        rtortosa_notebook_set_group_name,
                                        1);
  rb_define_module_function(module, 
                                        "notebook_get_group_name", 
                                        rtortosa_notebook_get_group_name,
                                        0);
  rb_define_module_function(module, 
                                        "notebook_get_current_page", 
                                        rtortosa_notebook_get_current_page,
                                        0);
  rb_define_module_function(module, 
                                        "notebook_get_n_pages", 
                                        rtortosa_notebook_get_n_pages,
                                        0);
  rb_define_module_function(module, 
                                        "notebook_set_current_page", 
                                        rtortosa_notebook_set_current_page,
                                        1);
  rb_define_module_function(module, 
                                        "notebook_next_page", 
                                        rtortosa_notebook_next_page,
                                        0);
  rb_define_module_function(module, 
                                        "notebook_prev_page", 
                                        rtortosa_notebook_prev_page,
                                        0);
  rb_define_module_function(module, 
                                        "notebook_set_show_border", 
                                        rtortosa_notebook_set_show_border,
                                        1);
  rb_define_module_function(module, 
                                        "notebook_get_show_border", 
                                        rtortosa_notebook_get_show_border,
                                        0);
  rb_define_module_function(module, 
                                        "notebook_set_show_tabs", 
                                        rtortosa_notebook_set_show_tabs,
                                        1);
  rb_define_module_function(module, 
                                        "notebook_get_show_tabs", 
                                        rtortosa_notebook_get_show_tabs,
                                        0);
  rb_define_module_function(module, 
                                        "notebook_set_scrollable", 
                                        rtortosa_notebook_set_scrollable,
                                        1);
  rb_define_module_function(module, 
                                        "notebook_get_scrollable", 
                                        rtortosa_notebook_get_scrollable,
                                        0);
  rb_define_module_function(module, 
                                        "notebook_popup_enable", 
                                        rtortosa_notebook_popup_enable,
                                        0);
  rb_define_module_function(module, 
                                        "notebook_popup_disable", 
                                        rtortosa_notebook_popup_disable,
                                        0);
}
