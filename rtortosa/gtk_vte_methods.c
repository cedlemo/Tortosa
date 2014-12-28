/*vte ruby class*/
#include "gtk_vte_methods.h"
static void close_tab_on_exit(GtkWidget * vte, gint status, backbone_t * backbone)
{
  gint current = gtk_notebook_get_current_page (GTK_NOTEBOOK(backbone->window.notebook));
  if (gtk_notebook_get_n_pages (GTK_NOTEBOOK(backbone->window.notebook)) > 1)
  {
    gtk_notebook_remove_page (GTK_NOTEBOOK(backbone->window.notebook), current );
    gtk_widget_grab_focus(
      gtk_notebook_get_nth_page(GTK_NOTEBOOK(backbone->window.notebook),
       gtk_notebook_get_current_page(GTK_NOTEBOOK(backbone->window.notebook))));
  
  }
  else
  {
    quit_gracefully(backbone);
  }
  SENTINEL("%d", status);  
}
static gchar* get_pid_dir(GPid pid)
{
  gchar* file = g_strdup_printf("/proc/%d/cwd", pid);
  gchar* link = g_file_read_link(file, NULL);
  g_free(file);
  return link;
}

static void c_vte_struct_free(vte_t *c)
{
  if(c)
  {
    //if(c->vte) {g_string_free(c->vte, TRUE);}
    ruby_xfree(c);
  }
}
static VALUE c_vte_struct_alloc( VALUE klass)
{
  return Data_Wrap_Struct(klass, NULL, c_vte_struct_free, ruby_xmalloc(sizeof(vte_t)));
}
static VALUE c_vte_initialize(VALUE self, VALUE command)
{
  vte_t *v;
  Data_Get_Struct(self, vte_t, v);
  if(command != Qnil && TYPE(command) != T_STRING)
    rb_raise(rb_eTypeError, "Expected a string");

  char **argvp=0;
  int argc;
  v->working_directory = NULL;
   
  v->command = command != Qnil ? command : rb_str_new2(g_getenv("SHELL"));
  if(g_shell_parse_argv(RSTRING_PTR(v->command), &argc, &argvp,0) != TRUE )
    g_shell_parse_argv(g_getenv("SHELL"), &argc, &argvp,0);
  GError *error = NULL;
  v->vte = vte_terminal_new();
  if( !vte_terminal_spawn_sync( VTE_TERMINAL(v->vte),
                                  VTE_PTY_DEFAULT,
                                  v->working_directory,
                                  argvp,
                                  NULL,
                                  G_SPAWN_SEARCH_PATH,
                                  NULL,
                                  NULL,
                                  &(v->pid),
                                  NULL,
                                  &error))
  {
    LOG_ERR("%s\\n", error->message);
    g_strfreev(argvp);
    /*TODO make a clean exit*/
    rb_raise(rb_eTypeError, "Unable to create a vte terminal");
  }
  g_strfreev(argvp);

  g_signal_connect(v->vte, "child-exited", G_CALLBACK(close_tab_on_exit), &backbone);

  int index = gtk_notebook_append_page(GTK_NOTEBOOK(backbone.window.notebook), v->vte, NULL);
  gtk_notebook_set_tab_reorderable( GTK_NOTEBOOK(backbone.window.notebook),
                                    v->vte, 
                                    TRUE);
  gtk_widget_show_all(backbone.window.notebook);
  gtk_notebook_set_current_page(GTK_NOTEBOOK(backbone.window.notebook), index);
  gtk_widget_grab_focus(v->vte);
  return self;
}
static VALUE rtortosa_terminal_copy_clipboard(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  vte_terminal_copy_clipboard(vte);
  return Qnil;
}
static VALUE rtortosa_terminal_paste_clipboard(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  vte_terminal_paste_clipboard(vte);
  return Qnil;
}
static VALUE rtortosa_terminal_copy_primary(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  vte_terminal_copy_primary(vte);
  return Qnil;
}
static VALUE rtortosa_terminal_paste_primary(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  vte_terminal_paste_primary(vte);
  return Qnil;
}
static VALUE rtortosa_terminal_select_all(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  vte_terminal_select_all(vte);
  return Qnil;
}
static VALUE rtortosa_terminal_unselect_all(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  vte_terminal_unselect_all(vte);
  return Qnil;
}
static VALUE rtortosa_terminal_set_size(VALUE self,VALUE columns,VALUE rows){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  glong c_columns;
  if (TYPE(columns) == T_FIXNUM)
    c_columns=FIX2LONG(columns);
  else if(TYPE(TYPE(columns) == T_BIGNUM))
    c_columns=NUM2LONG(columns);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  glong c_rows;
  if (TYPE(rows) == T_FIXNUM)
    c_rows=FIX2LONG(rows);
  else if(TYPE(TYPE(rows) == T_BIGNUM))
    c_rows=NUM2LONG(rows);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  vte_terminal_set_size(vte,c_columns,c_rows);
  return Qnil;
}
static VALUE rtortosa_terminal_set_font_scale(VALUE self,VALUE scale){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  if ((TYPE(scale) != T_FIXNUM) && (TYPE(scale) != T_BIGNUM))
    rb_raise(rb_eTypeError, "invalid type for input");
  gdouble c_scale=NUM2DBL(scale);
  vte_terminal_set_font_scale(vte,c_scale);
  return Qnil;
}
static VALUE rtortosa_terminal_get_font_scale(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gdouble ret =vte_terminal_get_font_scale(vte);

}
static VALUE rtortosa_terminal_set_audible_bell(VALUE self,VALUE is_audible){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean c_is_audible= (is_audible == Qtrue) ? TRUE : FALSE;
  vte_terminal_set_audible_bell(vte,c_is_audible);
  return Qnil;
}
static VALUE rtortosa_terminal_get_audible_bell(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean ret =vte_terminal_get_audible_bell(vte);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_terminal_set_scroll_on_output(VALUE self,VALUE scroll){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean c_scroll= (scroll == Qtrue) ? TRUE : FALSE;
  vte_terminal_set_scroll_on_output(vte,c_scroll);
  return Qnil;
}
static VALUE rtortosa_terminal_set_scroll_on_keystroke(VALUE self,VALUE scroll){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean c_scroll= (scroll == Qtrue) ? TRUE : FALSE;
  vte_terminal_set_scroll_on_keystroke(vte,c_scroll);
  return Qnil;
}
static VALUE rtortosa_terminal_set_rewrap_on_resize(VALUE self,VALUE rewrap){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean c_rewrap= (rewrap == Qtrue) ? TRUE : FALSE;
  vte_terminal_set_rewrap_on_resize(vte,c_rewrap);
  return Qnil;
}
static VALUE rtortosa_terminal_get_rewrap_on_resize(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean ret =vte_terminal_get_rewrap_on_resize(vte);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_terminal_set_color_bold(VALUE self,VALUE bold){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  VALUE m_Rtortosa = rb_const_get( rb_cObject, rb_intern( "Rtortosa" ));
  VALUE c_Color = rb_const_get_at( m_Rtortosa, rb_intern("Color") );
  if(rb_class_of(bold) != c_Color)
    rb_raise(rb_eTypeError, "invalid type for input");
  color_t *color_t_ptr;
  Data_Get_Struct(bold, color_t,color_t_ptr);
  GdkRGBA * c_bold= &(color_t_ptr->rgba);  vte_terminal_set_color_bold(vte,c_bold);
  return Qnil;
}
static VALUE rtortosa_terminal_set_color_foreground(VALUE self,VALUE foreground){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  VALUE m_Rtortosa = rb_const_get( rb_cObject, rb_intern( "Rtortosa" ));
  VALUE c_Color = rb_const_get_at( m_Rtortosa, rb_intern("Color") );
  if(rb_class_of(foreground) != c_Color)
    rb_raise(rb_eTypeError, "invalid type for input");
  color_t *color_t_ptr;
  Data_Get_Struct(foreground, color_t,color_t_ptr);
  GdkRGBA * c_foreground= &(color_t_ptr->rgba);  vte_terminal_set_color_foreground(vte,c_foreground);
  return Qnil;
}
static VALUE rtortosa_terminal_set_color_background(VALUE self,VALUE background){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  VALUE m_Rtortosa = rb_const_get( rb_cObject, rb_intern( "Rtortosa" ));
  VALUE c_Color = rb_const_get_at( m_Rtortosa, rb_intern("Color") );
  if(rb_class_of(background) != c_Color)
    rb_raise(rb_eTypeError, "invalid type for input");
  color_t *color_t_ptr;
  Data_Get_Struct(background, color_t,color_t_ptr);
  GdkRGBA * c_background= &(color_t_ptr->rgba);  vte_terminal_set_color_background(vte,c_background);
  return Qnil;
}
static VALUE rtortosa_terminal_set_color_cursor(VALUE self,VALUE cursor_background){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  VALUE m_Rtortosa = rb_const_get( rb_cObject, rb_intern( "Rtortosa" ));
  VALUE c_Color = rb_const_get_at( m_Rtortosa, rb_intern("Color") );
  if(rb_class_of(cursor_background) != c_Color)
    rb_raise(rb_eTypeError, "invalid type for input");
  color_t *color_t_ptr;
  Data_Get_Struct(cursor_background, color_t,color_t_ptr);
  GdkRGBA * c_cursor_background= &(color_t_ptr->rgba);  vte_terminal_set_color_cursor(vte,c_cursor_background);
  return Qnil;
}
static VALUE rtortosa_terminal_set_color_highlight(VALUE self,VALUE highlight_background){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  VALUE m_Rtortosa = rb_const_get( rb_cObject, rb_intern( "Rtortosa" ));
  VALUE c_Color = rb_const_get_at( m_Rtortosa, rb_intern("Color") );
  if(rb_class_of(highlight_background) != c_Color)
    rb_raise(rb_eTypeError, "invalid type for input");
  color_t *color_t_ptr;
  Data_Get_Struct(highlight_background, color_t,color_t_ptr);
  GdkRGBA * c_highlight_background= &(color_t_ptr->rgba);  vte_terminal_set_color_highlight(vte,c_highlight_background);
  return Qnil;
}
static VALUE rtortosa_terminal_set_color_highlight_foreground(VALUE self,VALUE highlight_foreground){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  VALUE m_Rtortosa = rb_const_get( rb_cObject, rb_intern( "Rtortosa" ));
  VALUE c_Color = rb_const_get_at( m_Rtortosa, rb_intern("Color") );
  if(rb_class_of(highlight_foreground) != c_Color)
    rb_raise(rb_eTypeError, "invalid type for input");
  color_t *color_t_ptr;
  Data_Get_Struct(highlight_foreground, color_t,color_t_ptr);
  GdkRGBA * c_highlight_foreground= &(color_t_ptr->rgba);  vte_terminal_set_color_highlight_foreground(vte,c_highlight_foreground);
  return Qnil;
}
static VALUE rtortosa_terminal_set_default_colors(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  vte_terminal_set_default_colors(vte);
  return Qnil;
}
static VALUE rtortosa_terminal_set_scrollback_lines(VALUE self,VALUE lines){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  glong c_lines;
  if (TYPE(lines) == T_FIXNUM)
    c_lines=FIX2LONG(lines);
  else if(TYPE(TYPE(lines) == T_BIGNUM))
    c_lines=NUM2LONG(lines);
  else
    rb_raise(rb_eTypeError, "invalid type for input");
  vte_terminal_set_scrollback_lines(vte,c_lines);
  return Qnil;
}
static VALUE rtortosa_terminal_set_allow_bold(VALUE self,VALUE allow_bold){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean c_allow_bold= (allow_bold == Qtrue) ? TRUE : FALSE;
  vte_terminal_set_allow_bold(vte,c_allow_bold);
  return Qnil;
}
static VALUE rtortosa_terminal_get_allow_bold(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean ret =vte_terminal_get_allow_bold(vte);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_terminal_get_has_selection(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean ret =vte_terminal_get_has_selection(vte);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_terminal_set_mouse_autohide(VALUE self,VALUE setting){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean c_setting= (setting == Qtrue) ? TRUE : FALSE;
  vte_terminal_set_mouse_autohide(vte,c_setting);
  return Qnil;
}
static VALUE rtortosa_terminal_get_mouse_autohide(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean ret =vte_terminal_get_mouse_autohide(vte);
  return ret? Qtrue: Qfalse;
}
static VALUE rtortosa_terminal_reset(VALUE self,VALUE clear_tabstops,VALUE clear_history){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean c_clear_tabstops= (clear_tabstops == Qtrue) ? TRUE : FALSE;
  gboolean c_clear_history= (clear_history == Qtrue) ? TRUE : FALSE;
  vte_terminal_reset(vte,c_clear_tabstops,c_clear_history);
  return Qnil;
}
static VALUE rtortosa_terminal_get_cursor_position(VALUE self,VALUE column,VALUE row){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  glong local_c_column;
  glong * c_column = &local_c_column;
  glong local_c_row;
  glong * c_row = &local_c_row;
  vte_terminal_get_cursor_position(vte,c_column,c_row);
  VALUE ret= rb_ary_new();
  rb_ary_push(ret, column);
  rb_ary_push(ret, row);
  return ret;

}
static VALUE rtortosa_terminal_get_encoding(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  const char * ret =vte_terminal_get_encoding(vte);
  return rb_str_new2(ret);
}
static VALUE rtortosa_terminal_get_cjk_ambiguous_width(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  int ret =vte_terminal_get_cjk_ambiguous_width(vte);
  return INT2FIX(ret);
}
static VALUE rtortosa_terminal_get_char_width(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  glong ret =vte_terminal_get_char_width(vte);

}
static VALUE rtortosa_terminal_get_char_height(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  glong ret =vte_terminal_get_char_height(vte);

}
static VALUE rtortosa_terminal_get_row_count(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  glong ret =vte_terminal_get_row_count(vte);

}
static VALUE rtortosa_terminal_get_column_count(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  glong ret =vte_terminal_get_column_count(vte);

}
static VALUE rtortosa_terminal_get_window_title(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  const char * ret =vte_terminal_get_window_title(vte);
  return rb_str_new2(ret);
}
static VALUE rtortosa_terminal_get_icon_title(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  const char * ret =vte_terminal_get_icon_title(vte);
  return rb_str_new2(ret);
}
static VALUE rtortosa_terminal_get_current_directory_uri(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  const char * ret =vte_terminal_get_current_directory_uri(vte);
  return rb_str_new2(ret);
}
static VALUE rtortosa_terminal_get_current_file_uri(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  const char * ret =vte_terminal_get_current_file_uri(vte);
  return rb_str_new2(ret);
}
static VALUE rtortosa_terminal_set_input_enabled(VALUE self,VALUE enabled){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean c_enabled= (enabled == Qtrue) ? TRUE : FALSE;
  vte_terminal_set_input_enabled(vte,c_enabled);
  return Qnil;
}
static VALUE rtortosa_terminal_get_input_enabled(VALUE self){
  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
  gboolean ret =vte_terminal_get_input_enabled(vte);
  return ret? Qtrue: Qfalse;
}
VALUE generate_vte_ruby_class_under(VALUE module) {
  VALUE c_vte = rb_define_class_under(module, "Vte", rb_cObject);
  rb_define_alloc_func(c_vte, c_vte_struct_alloc);
  rb_define_method(c_vte, "initialize", RUBY_METHOD_FUNC(c_vte_initialize), 1);

  rb_define_method(c_vte,
                                        "copy_clipboard",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_copy_clipboard),
                                        0);
  rb_define_method(c_vte,
                                        "paste_clipboard",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_paste_clipboard),
                                        0);
  rb_define_method(c_vte,
                                        "copy_primary",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_copy_primary),
                                        0);
  rb_define_method(c_vte,
                                        "paste_primary",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_paste_primary),
                                        0);
  rb_define_method(c_vte,
                                        "select_all",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_select_all),
                                        0);
  rb_define_method(c_vte,
                                        "unselect_all",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_unselect_all),
                                        0);
  rb_define_method(c_vte,
                                        "set_size",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_size),
                                        2);
  rb_define_method(c_vte,
                                        "set_font_scale",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_font_scale),
                                        1);
  rb_define_method(c_vte,
                                        "get_font_scale",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_font_scale),
                                        0);
  rb_define_method(c_vte,
                                        "set_audible_bell",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_audible_bell),
                                        1);
  rb_define_method(c_vte,
                                        "get_audible_bell",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_audible_bell),
                                        0);
  rb_define_method(c_vte,
                                        "set_scroll_on_output",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_scroll_on_output),
                                        1);
  rb_define_method(c_vte,
                                        "set_scroll_on_keystroke",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_scroll_on_keystroke),
                                        1);
  rb_define_method(c_vte,
                                        "set_rewrap_on_resize",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_rewrap_on_resize),
                                        1);
  rb_define_method(c_vte,
                                        "get_rewrap_on_resize",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_rewrap_on_resize),
                                        0);
  rb_define_method(c_vte,
                                        "set_color_bold",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_color_bold),
                                        1);
  rb_define_method(c_vte,
                                        "set_color_foreground",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_color_foreground),
                                        1);
  rb_define_method(c_vte,
                                        "set_color_background",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_color_background),
                                        1);
  rb_define_method(c_vte,
                                        "set_color_cursor",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_color_cursor),
                                        1);
  rb_define_method(c_vte,
                                        "set_color_highlight",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_color_highlight),
                                        1);
  rb_define_method(c_vte,
                                        "set_color_highlight_foreground",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_color_highlight_foreground),
                                        1);
  rb_define_method(c_vte,
                                        "set_default_colors",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_default_colors),
                                        0);
  rb_define_method(c_vte,
                                        "set_scrollback_lines",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_scrollback_lines),
                                        1);
  rb_define_method(c_vte,
                                        "set_allow_bold",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_allow_bold),
                                        1);
  rb_define_method(c_vte,
                                        "get_allow_bold",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_allow_bold),
                                        0);
  rb_define_method(c_vte,
                                        "get_has_selection",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_has_selection),
                                        0);
  rb_define_method(c_vte,
                                        "set_mouse_autohide",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_mouse_autohide),
                                        1);
  rb_define_method(c_vte,
                                        "get_mouse_autohide",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_mouse_autohide),
                                        0);
  rb_define_method(c_vte,
                                        "reset",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_reset),
                                        2);
  rb_define_method(c_vte,
                                        "get_cursor_position",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_cursor_position),
                                        0);
  rb_define_method(c_vte,
                                        "get_encoding",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_encoding),
                                        0);
  rb_define_method(c_vte,
                                        "get_cjk_ambiguous_width",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_cjk_ambiguous_width),
                                        0);
  rb_define_method(c_vte,
                                        "get_char_width",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_char_width),
                                        0);
  rb_define_method(c_vte,
                                        "get_char_height",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_char_height),
                                        0);
  rb_define_method(c_vte,
                                        "get_row_count",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_row_count),
                                        0);
  rb_define_method(c_vte,
                                        "get_column_count",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_column_count),
                                        0);
  rb_define_method(c_vte,
                                        "get_window_title",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_window_title),
                                        0);
  rb_define_method(c_vte,
                                        "get_icon_title",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_icon_title),
                                        0);
  rb_define_method(c_vte,
                                        "get_current_directory_uri",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_current_directory_uri),
                                        0);
  rb_define_method(c_vte,
                                        "get_current_file_uri",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_current_file_uri),
                                        0);
  rb_define_method(c_vte,
                                        "set_input_enabled",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_set_input_enabled),
                                        1);
  rb_define_method(c_vte,
                                        "get_input_enabled",
                                        RUBY_METHOD_FUNC(rtortosa_terminal_get_input_enabled),
                                        0);
}
