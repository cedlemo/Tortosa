#!/usr/bin/env ruby
require './gtk_parser'
source = '/usr/include/vte-2.91/vte/vteterminal.h'
hp = `pkg-config --cflags gtk+-3.0`.gsub('-I', '').split(' ')
wrapper = Wrapper::GlobalWrapper.new(source, hp)
wrapper.parse(true)

filter = Wrapper::FunctionsFilter.new

names=['gtk_window_set_has_resize_grip', 'gtk_window_reshow_with_initial_size',
       'gtk_window_get_has_resize_grip', 'gtk_window_resize_grip_is_visible',
       'vte_terminal_set_colors', 'vte_terminal_search_', 'vte_terminal_match'
]
names.each do |n|
  filter.add_name_to_reject(n)
end

return_types=['int','char','boolean','void']
return_types.each do |r|
  filter.add_return_type_to_match(r)
end

to_match =['(const\s)*\s*int\s*\*', '(const\s)*\s*gchar\s*\*', 'gboolean',
           'void', 'GtkNotebook\s+\*', 'GtkPositionType','VteTerminal\s+\*',
           '(const\s)*\s*GdkRGBA\s+\*']

to_match.each do |m|
  filter.add_param_to_match(m)
end

sorter = Wrapper::FunctionsWrapper.new(wrapper.parser.getFunctions, filter)

sorter.sort

rewritte = Wrapper::Rewritter.new

fq = Wrapper::FunctionQualifier.new
fq.is_void_instructions do |function|
  function.getReturn.getName.match(/void/)
end
fq.is_getter_instructions do |function|
  fq.is_void(function) && function.getName.match(/_get_/) ? true : false
end

def build_void_getter_return(f)
 s = '  VALUE ret= rb_ary_new();' + Wrapper::NEWLINE
  f.getParameters.each do |p|
    case
    when p.getType.getName.match(/gint \*/)
      s += "  rb_ary_push(ret, INT2FIX(#{p.getName}));" + Wrapper::NEWLINE
    when p.getType.getName.match(/gchar \*/)
      s += "  rb_ary_push(ret, rb_str_new2(#{p.getName}));" + Wrapper::NEWLINE
    else
      ''
    end
  end
  s += '  return ret;'
end

rewritte.wrapper_r_return_instructions do |function|
  type = function.getReturn.getName
  if fq.is_getter(function)
    build_void_getter_return(function)
  else
    case
    when type =~ /(g)*int/
      '  return INT2FIX(ret);'
    when type =~ /.*char\s+\*/
      '  return rb_str_new2(ret);'
    when type == "gboolean"
      '  return ret? Qtrue: Qfalse;'
    when type == "void"
      '  return Qnil;'
    else
      ""
    end
  end
end

rewritte.wrapper_r_2_c_instructions do |parameter|
  type = parameter.getType.getName
  name = parameter.getName
  case
  when type == "gint"
    %Q{  if (TYPE(#{name}) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  #{type} r_#{name}=FIX2INT(#{name});
}
  when type =~ /.*char\s+\*/
    %Q{  if(TYPE(#{name}) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  #{type} r_#{name}=RSTRING_PTR(#{name});
}
  when type == "gboolean"
    %Q{  gboolean r_#{name}= (#{name} == Qtrue) ? TRUE : FALSE;
}
  when type == "gint *"
    %Q{  gint #{name};
  #{type} r_#{name} = &#{name};
}
  when type == "const GdkRGBA *"
    %Q{  VALUE m_Rtortosa = rb_const_get( rb_cObject, rb_intern( "Rtortosa" ));
  VALUE c_Color = rb_const_get_at( m_Rtortosa, rb_intern("Color") );
  if(rb_class_of(#{name}) != c_Color)
    rb_raise(rb_eTypeError, "invalid type for input");
  color_t *c;
  Data_Get_Struct(#{name}, color_t,c);
  GdkRGBA * r_#{name}= &(c->rgba);
}
  when type =~ /VteTerminal\s*\*/
    %Q{  vte_t *v;
  Data_Get_Struct(self, vte_t,v);
  VteTerminal * vte = VTE_TERMINAL(v->vte);
}
  else
    ''
  end
end

rewritte.wrapper_r_arguments_instructions do |parameter|
  parameter.getType.getName =~ /gint\s\*|GtkNotebook\s\*|VteTerminal\s\*/ ?
  "VALUE self" : ", VALUE #{parameter.getName}" 
end

rewritte.rename_instructions do |name|
  "rtortosa_#{name.gsub("vte_","")}"
end

rewritte.wrapper_c_arguments_instructions do |parameter|
  if parameter.getType.getName == 'VteTerminal *'
    'vte'
  else
    "r_#{parameter.getName}"
  end
end

def print_function(f)
  puts "#{f.getReturn.getName} #{f.getName}( #{f.getParameters.map{|p|"#{p.getType.getName} #{p.getName}"}.join(",")})"
end

out = Wrapper::OutputFiles.new('../gtk_vte_methods')
out._h.puts(<<HEADER)
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
HEADER
out._c.puts(<<CCODE)
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
CCODE
def write_rdoc_comments(function)
  %Q{/*
*call-seq:
*Rtortosa::Vte::#{function.getName} -> 
*/
}
end
sorter.functions_to_parse.each do |f|
  s = "static VALUE " + rewritte.rename(f.getName) + Wrapper::O_BRACKET
  f.getParameters.each do |p|
    s+= rewritte.wrapper_r_arguments(p) 
  end
  s +=  Wrapper::C_BRACKET + Wrapper::O_CURLY_BRACKET + Wrapper::NEWLINE
  f.getParameters.each do |p|
    s += rewritte.wrapper_r_2_c(p) 
  end
  s += "  "
  s += "#{f.getReturn.getName} ret =" unless fq.is_void(f) 
  s +=  f.getName + Wrapper::O_BRACKET  
  buff = []
  f.getParameters.each do |p|
    buff << rewritte.wrapper_c_arguments(p)
  end  
  s += buff.join(Wrapper::COMMA) + Wrapper::C_BRACKET + Wrapper::SEMI_COLON + Wrapper::NEWLINE
  s +=  rewritte.wrapper_r_return(f)
  s += Wrapper::NEWLINE + Wrapper::C_CURLY_BRACKET
  out._c.puts(s)
end
out._c.puts(<<WRAPPER)
VALUE generate_vte_ruby_class_under(VALUE module) {
  VALUE c_vte = rb_define_class_under(module, "Vte", rb_cObject);
  rb_define_alloc_func(c_vte, c_vte_struct_alloc);
  rb_define_method(c_vte, "initialize", RUBY_METHOD_FUNC(c_vte_initialize), 1);
WRAPPER
def get_callback_parameters_number(params)
  if params.any? {|p| p.getType.getName == 'VteTerminal *'}
    params.size - 1
  else
    params.size
  end
end
sorter.functions_to_parse.each do |f|
  out._c.puts( %Q{  rb_define_method(c_vte, 
                                        "#{f.getName.gsub('vte_terminal_','')}", 
                                        RUBY_METHOD_FUNC(rtortosa_#{f.getName.gsub('vte_','')}),
                                        #{fq.is_getter(f) ? 0 : 
                                        get_callback_parameters_number(f.getParameters)});} + 
  Wrapper::NEWLINE)
end
out._c.puts(Wrapper::C_CURLY_BRACKET)
# write informations about handled functions and not handled
out._h.puts(<<INFOS)
/*|--------------------------------------->>*/
/* functions wrapped                        */
/*<<---------------------------------------|*/
INFOS
sorter.functions_to_parse.each {|f| out._h.puts('//' + f.getName)}
out._h.puts(<<INFOS)
/*|--------------------------------------->>*/
/* functions ignored                        */
/*<<---------------------------------------|*/
INFOS
sorter.functions_to_reject.each {|f| out._h.puts('//' + f.getName)}

out.close_all
