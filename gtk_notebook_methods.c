 /*notebook ruby class*/
#include "gtk_notebook_methods.h"

static void c_notebook_struct_free(notebook_t *c)
{
  if(c)
  {
    ruby_xfree(c);
  }
}
static VALUE c_notebook_struct_alloc( VALUE klass)
{
  return Data_Wrap_Struct(klass, NULL, c_notebook_struct_free, ruby_xmalloc(sizeof(notebook_t)));
}
/*static VALUE c_notebook_initialize(VALUE self)
{
}*/
static VALUE rtortosa_notebook_set_group_name(VALUE self,VALUE group_name){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  if(TYPE(group_name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_group_name=RSTRING_PTR(group_name);
  gtk_notebook_set_group_name(notebook,c_group_name);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_notebook_get_group_name(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  const gchar * c_ret =gtk_notebook_get_group_name(notebook);
  VALUE r_ret = rb_str_new2(c_ret);

  return r_ret;

}
static VALUE rtortosa_notebook_get_current_page(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  gint c_ret =gtk_notebook_get_current_page(notebook);
  VALUE r_ret = INT2NUM((int) c_ret);

  return r_ret;

}
static VALUE rtortosa_notebook_get_n_pages(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  gint c_ret =gtk_notebook_get_n_pages(notebook);
  VALUE r_ret = INT2NUM((int) c_ret);

  return r_ret;

}
static VALUE rtortosa_notebook_next_page(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  gtk_notebook_next_page(notebook);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_notebook_prev_page(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  gtk_notebook_prev_page(notebook);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_notebook_set_show_border(VALUE self,VALUE show_border){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  gboolean c_show_border= (show_border == Qtrue) ? TRUE : FALSE;
  gtk_notebook_set_show_border(notebook,c_show_border);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_notebook_get_show_border(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  gboolean c_ret =gtk_notebook_get_show_border(notebook);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_notebook_set_show_tabs(VALUE self,VALUE show_tabs){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  gboolean c_show_tabs= (show_tabs == Qtrue) ? TRUE : FALSE;
  gtk_notebook_set_show_tabs(notebook,c_show_tabs);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_notebook_get_show_tabs(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  gboolean c_ret =gtk_notebook_get_show_tabs(notebook);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_notebook_set_tab_pos(VALUE self,VALUE pos){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  GtkPositionType c_pos;
  if (TYPE(pos) == T_FIXNUM)
    c_pos=FIX2INT(pos);
  else if(TYPE(TYPE(pos) == T_BIGNUM))
    c_pos=NUM2INT(pos);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gtk_notebook_set_tab_pos(notebook,c_pos);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_notebook_set_scrollable(VALUE self,VALUE scrollable){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  gboolean c_scrollable= (scrollable == Qtrue) ? TRUE : FALSE;
  gtk_notebook_set_scrollable(notebook,c_scrollable);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_notebook_get_scrollable(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  gboolean c_ret =gtk_notebook_get_scrollable(notebook);
  VALUE r_ret = c_ret == TRUE ? Qtrue : Qfalse;

  return r_ret;

}
static VALUE rtortosa_notebook_popup_enable(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  gtk_notebook_popup_enable(notebook);
 VALUE r_ret= Qnil;
  return r_ret;

}
static VALUE rtortosa_notebook_popup_disable(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->widget);
  gtk_notebook_popup_disable(notebook);
 VALUE r_ret= Qnil;
  return r_ret;

}
VALUE generate_notebook_ruby_class_under(VALUE module, VALUE superclass) {
  VALUE c_notebook = rb_define_class_under(module, "Notebook", superclass);
  rb_define_const(module, "POS_LEFT", INT2FIX(GTK_POS_LEFT) );
  rb_define_const(module, "POS_RIGHT", INT2FIX(GTK_POS_RIGHT) );
  rb_define_const(module, "POS_TOP", INT2FIX(GTK_POS_TOP) );
  rb_define_const(module, "POS_BOTTOM", INT2FIX(GTK_POS_BOTTOM));
  rb_define_alloc_func(c_notebook, c_notebook_struct_alloc);

  rb_define_method(c_notebook,
                                        "set_group_name",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_set_group_name),
                                        1);
  rb_define_method(c_notebook,
                                        "get_group_name",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_group_name),
                                        0);
  rb_define_method(c_notebook,
                                        "get_current_page",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_current_page),
                                        0);
  rb_define_method(c_notebook,
                                        "get_n_pages",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_n_pages),
                                        0);
  rb_define_method(c_notebook,
                                        "next_page",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_next_page),
                                        0);
  rb_define_method(c_notebook,
                                        "prev_page",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_prev_page),
                                        0);
  rb_define_method(c_notebook,
                                        "set_show_border",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_set_show_border),
                                        1);
  rb_define_method(c_notebook,
                                        "get_show_border",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_show_border),
                                        0);
  rb_define_method(c_notebook,
                                        "set_show_tabs",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_set_show_tabs),
                                        1);
  rb_define_method(c_notebook,
                                        "get_show_tabs",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_show_tabs),
                                        0);
  rb_define_method(c_notebook,
                                        "set_tab_pos",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_set_tab_pos),
                                        1);
  rb_define_method(c_notebook,
                                        "set_scrollable",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_set_scrollable),
                                        1);
  rb_define_method(c_notebook,
                                        "get_scrollable",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_scrollable),
                                        0);
  rb_define_method(c_notebook,
                                        "popup_enable",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_popup_enable),
                                        0);
  rb_define_method(c_notebook,
                                        "popup_disable",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_popup_disable),
                                        0);
  return c_notebook;
}
