/*notebook ruby class*/
#include "gtk_notebooks_methods.h"

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
/*static VALUE c_notebook_initialize(VALUE self, VALUE command)
{
}*/
static VALUE rtortosa_notebook_set_group_name(VALUE self,VALUE group_name){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  if(TYPE(group_name) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  const gchar * c_group_name=RSTRING_PTR(group_name);
  gtk_notebook_set_group_name(notebook,c_group_name);
  return Qnil;
}
static VALUE rtortosa_notebook_get_group_name(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  const gchar * ret =gtk_notebook_get_group_name(notebook);
  return rb_str_new2(ret);
}
static VALUE rtortosa_notebook_get_current_page(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  gint ret =gtk_notebook_get_current_page(notebook);
  return INT2FIX(ret);
}
static VALUE rtortosa_notebook_get_n_pages(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  gint ret =gtk_notebook_get_n_pages(notebook);
  return INT2FIX(ret);
}
static VALUE rtortosa_notebook_next_page(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  gtk_notebook_next_page(notebook);
  return Qnil;
}
static VALUE rtortosa_notebook_prev_page(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  gtk_notebook_prev_page(notebook);
  return Qnil;
}
static VALUE rtortosa_notebook_set_show_border(VALUE self,VALUE show_border){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  gboolean c_show_border= (show_border == Qtrue) ? TRUE : FALSE;
  gtk_notebook_set_show_border(notebook,c_show_border);
  return Qnil;
}
static VALUE rtortosa_notebook_get_show_border(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  gboolean ret =gtk_notebook_get_show_border(notebook);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_notebook_set_show_tabs(VALUE self,VALUE show_tabs){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  gboolean c_show_tabs= (show_tabs == Qtrue) ? TRUE : FALSE;
  gtk_notebook_set_show_tabs(notebook,c_show_tabs);
  return Qnil;
}
static VALUE rtortosa_notebook_get_show_tabs(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  gboolean ret =gtk_notebook_get_show_tabs(notebook);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_notebook_set_tab_pos(VALUE self,VALUE pos){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  GtkPositionType c_pos
  if (TYPE(pos) == T_FIXNUM)
    c_pos=FIX2INT(pos);
  else if(TYPE(TYPE(pos) == T_BIGNUM))
    c_pos=NUM2INT(pos);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  gtk_notebook_set_tab_pos(notebook,c_pos);
  return Qnil;
}
static VALUE rtortosa_notebook_set_scrollable(VALUE self,VALUE scrollable){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  gboolean c_scrollable= (scrollable == Qtrue) ? TRUE : FALSE;
  gtk_notebook_set_scrollable(notebook,c_scrollable);
  return Qnil;
}
static VALUE rtortosa_notebook_get_scrollable(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  gboolean ret =gtk_notebook_get_scrollable(notebook);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_notebook_get_tab_hborder(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  guint16 ret =gtk_notebook_get_tab_hborder(notebook);
  return INT2FIX(ret);
}
static VALUE rtortosa_notebook_get_tab_vborder(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  guint16 ret =gtk_notebook_get_tab_vborder(notebook);
  return INT2FIX(ret);
}
static VALUE rtortosa_notebook_popup_enable(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  gtk_notebook_popup_enable(notebook);
  return Qnil;
}
static VALUE rtortosa_notebook_popup_disable(VALUE self){
  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
  gtk_notebook_popup_disable(notebook);
  return Qnil;
}
VALUE generate_notebook_ruby_class_under(VALUE module) {
  VALUE c_notebook = rb_define_class_under(module, "Notebook", rb_cObject);
  rb_define_alloc_func(c_notebook, c_notebook_struct_alloc);
  //rb_define_method(c_vte, "initialize", RUBY_METHOD_FUNC(c_vte_initialize), 1);

  rb_define_method(c_vte,
                                        "set_group_name",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_set_group_name),
                                        1);
  rb_define_method(c_vte,
                                        "get_group_name",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_group_name),
                                        0);
  rb_define_method(c_vte,
                                        "get_current_page",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_current_page),
                                        0);
  rb_define_method(c_vte,
                                        "get_n_pages",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_n_pages),
                                        0);
  rb_define_method(c_vte,
                                        "next_page",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_next_page),
                                        0);
  rb_define_method(c_vte,
                                        "prev_page",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_prev_page),
                                        0);
  rb_define_method(c_vte,
                                        "set_show_border",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_set_show_border),
                                        1);
  rb_define_method(c_vte,
                                        "get_show_border",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_show_border),
                                        0);
  rb_define_method(c_vte,
                                        "set_show_tabs",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_set_show_tabs),
                                        1);
  rb_define_method(c_vte,
                                        "get_show_tabs",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_show_tabs),
                                        0);
  rb_define_method(c_vte,
                                        "set_tab_pos",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_set_tab_pos),
                                        1);
  rb_define_method(c_vte,
                                        "set_scrollable",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_set_scrollable),
                                        1);
  rb_define_method(c_vte,
                                        "get_scrollable",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_scrollable),
                                        0);
  rb_define_method(c_vte,
                                        "get_tab_hborder",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_tab_hborder),
                                        0);
  rb_define_method(c_vte,
                                        "get_tab_vborder",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_get_tab_vborder),
                                        0);
  rb_define_method(c_vte,
                                        "popup_enable",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_popup_enable),
                                        0);
  rb_define_method(c_vte,
                                        "popup_disable",
                                        RUBY_METHOD_FUNC(rtortosa_notebook_popup_disable),
                                        0);
}
