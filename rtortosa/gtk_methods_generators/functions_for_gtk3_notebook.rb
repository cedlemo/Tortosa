#!/usr/bin/env ruby

require 'rtruckboris'

gtk_notebook = '/usr/include/gtk-3.0/gtk/gtknotebook.h'
header_paths = `pkg-config --cflags gtk+-3.0`.gsub('-I', '').split(' ')
# get gcc include if needed
gcc_lib_base='/usr/lib/gcc/' << `llvm-config --host-target`.chomp << '/*'
gcc_lib = Dir.glob(gcc_lib_base ).sort.last + '/include'
header_paths << gcc_lib
header_paths << '/usr/include'

parser = Rtruckboris::HeaderParser.new(gtk_notebook, header_paths)
parser.parse(true)

functions = parser.getFunctions()

NEWLINE ="\n"
O_BRACKET ="("
C_BRACKET = ")"
O_CURLY_BRACKET = "{"
C_CURLY_BRACKET = "}"
COMMA = ","
SEMI_COLON = ";"

def in_typemap(p)
  type = p.getType.getName
  return case
  when type == "gint"
    %Q{  if (TYPE(#{p.getName}) != T_FIXNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  #{type} r_#{p.getName}=FIX2INT(#{p.getName});}
  when type =~ /.*char\s+\*/
    %Q{  if(TYPE(#{p.getName}) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  #{type} r_#{p.getName}=RSTRING_PTR(#{p.getName});}
  when type == "gboolean"
    %Q{  gboolean r_#{p.getName}= (#{p.getName} == Qtrue) ? TRUE : FALSE;}
  when type == "GtkNotebook *"
    ''
  when type == "gint *"
    %Q{  gint #{p.getName};
      #{  p.getType.getName} r_#{p.getName} = &#{p.getName};}
  else
    ''
  end
end

def function_is_void_getter(f)
  res = false
  res = true if (f.getName.match(/_get_/) && f.getReturn.getName.match(/void/))
  res
end

def build_void_getter_return(f)
 s = '  VALUE ret= rb_ary_new();' + NEWLINE
  f.getParameters.each do |p|
    case
    when p.getType.getName.match(/gint \*/)
      s += "  rb_ary_push(ret, INT2FIX(#{p.getName}));" + NEWLINE
    else
      ''
    end
  end
  s += 'return ret;'
end

def out_typemap(f)
  type = f.getReturn.getName
  if function_is_void_getter(f)
    build_void_getter_return(f)
  else
    return case
    when type == "gint"
      '  return INT2FIX(ret);'
    when type =~ /.*char\s+\*/
      '  return rb_strnew2(ret);'
    when type == "gboolean"
      '  return ret? Qtrue: Qfalse;'
    when type == "void"
      '  return Qnil;'
    else
      ""
    end
  end
end

def rename(name)
  "static VALUE rtortosa_#{name.gsub("gtk_","")}#{O_BRACKET}VALUE self"
end

def build_c_params(params)
  buf=[]
  params.each do |p|
    if p.getType.getName == 'GtkNotebook *'
      buf << 'GTK_NOTEBOOK(backbone.window.notebook)'
    else
      buf << "r_#{p.getName}"
    end
  end
  buf.join(COMMA)
end

def get_callback_parameters_number(params)
  if params.any? {|p| p.getType.getName == 'GtkNotebook *'}
    params.size - 1
  else
    params.size
  end
end

def build_ruby_wrapper(f)
  params = f.getParameters
  s = rename(f.getName)
  params.each do |p|
    s += ", VALUE #{p.getName}" unless p.getType.getName =~ /gint\s\*|GtkNotebook\s\*/
  end
  s += C_BRACKET + O_CURLY_BRACKET + NEWLINE
  params.each do |p|
    r2c = in_typemap(p)
    s += r2c + NEWLINE unless r2c == ''
  end
  s += "  "
  s += "#{f.getReturn.getName} ret =" unless f.getReturn.getName =~ /void/
  s += f.getName + O_BRACKET + build_c_params(params) + C_BRACKET + SEMI_COLON + NEWLINE
  s += out_typemap(f) + NEWLINE
  s += C_CURLY_BRACKET + NEWLINE
  s
end

functions_to_parse = []
functions_rejected = []

def print_function(f)
  puts "#{f.getReturn.getName} #{f.getName}( #{f.getParameters.map{|p|"#{p.getType.getName} #{p.getName}"}.join(",")})"
end

def to_be_rejected_on_params(params, f)
  ret = false
  params.each do |p|
    if !p.getType.getName.match(/((const)*\s*gint)|((const)*\s*gchar)|(gboolean)|(void)|(GtkNotebook\s+\*)/)
      ret = true
#    elsif p.getType.getName.match(/GtkWindow\s+\*/) && p.getName != 'window'
#      ret = true
    end
  end
  ret
end

def to_be_rejected_on_return_type(type)
  !(type =~ /(gint)|(gchar)|(gboolean)|(void)/)
end

def to_be_rejected_on_deprecation_usage(function_name)
  my_regexes = []
  my_regexes << 'gtk_window_set_has_resize_grip'
  my_regexes << 'gtk_window_reshow_with_initial_size'
  my_regexes << 'gtk_window_get_has_resize_grip'
  my_regexes << 'gtk_window_resize_grip_is_visible'
  reg = "(" << my_regexes.join(")|(") << ")"
  function_name =~ /#{reg}/
end

functions.each do |f|
  if !to_be_rejected_on_return_type(f.getReturn.getName) && !to_be_rejected_on_params(f.getParameters,f) && !to_be_rejected_on_deprecation_usage(f.getName)
    functions_to_parse << f
  else
    functions_rejected << f
  end
end


def write_gtkwindow_wrapper(functions)
  s = 'void gtk_notebook_wrapper(VALUE module)' + O_CURLY_BRACKET + NEWLINE
  s += '  rb_define_const(module, "POS_LEFT", INT2FIX(GTK_POS_LEFT) );' + NEWLINE
  s += '  rb_define_const(module, "POS_RIGHT", INT2FIX(GTK_POS_RIGHT) );' + NEWLINE
  s += '  rb_define_const(module, "POS_TOP", INT2FIX(GTK_POS_TOP) );' + NEWLINE
  s += '  rb_define_const(module, "POS_BOTTOM", INT2FIX(GTK_POS_BOTTOM));' + NEWLINE
  functions.each do |f|
    s += %Q{  rb_define_module_function(module, 
                                        "#{f.getName.gsub('gtk_','')}", 
                                        rtortosa_#{f.getName.gsub('gtk_','')},
                                        #{function_is_void_getter(f) ? 0 : get_callback_parameters_number(f.getParameters)});} + NEWLINE
  end
  s += C_CURLY_BRACKET
end
wrapper_c = File.new('../gtk_notebook_methods.c', 'w')
wrapper_h = File.new('../gtk_notebook_methods.h', 'w')

wrapper_h.puts('#ifndef GTK_NOTEBOOK_METHODS_H')
wrapper_h.puts('#define GTK_NOTEBOOK_METHODS_H')
wrapper_h.puts('#include <ruby.h>')
wrapper_h.puts('#include <gtk/gtk.h>')
wrapper_h.puts('#include "backbone.h"')
wrapper_h.puts('void gtk_notebook_wrapper(VALUE);')
wrapper_h.puts('#endif')

wrapper_c.puts('#include "gtk_notebook_methods.h"')
functions_to_parse.each {|f| wrapper_c.puts(build_ruby_wrapper(f))}
wrapper_c.puts(write_gtkwindow_wrapper(functions_to_parse))

wrapper_c.close
wrapper_h.close
