#!/usr/bin/env ruby
require './gtk_parser'
# Parse the source files and get the functions all
source = '/usr/include/gtk-3.0/gtk/gtknotebook.h'
hp = `pkg-config --cflags gtk+-3.0`.gsub('-I', '').split(' ')
wrapper = Wrapper::GlobalWrapper.new(source, hp)
wrapper.parse(true)
# Create a filter in order to check sort the functions
# we would like to parse and those we don't want

filter = Wrapper::FunctionsFilter.new

#names = %w(vte_terminal_search_ vte_terminal_match)
#names.each do |n|
#  filter.add_name_to_reject(n)
#end

return_types = %w(int char boolean void long double uint16)
return_types.each do |r|
  filter.add_return_type_to_match(r)
end

to_match = ['(const\s)*\s*int\s*\*', '(const\s)*\s*gchar\s*\*', '(g)*boolean',
            'void', 'GtkNotebook\s+\*', 'GtkPositionType',
            '(g)*double', '(g)*long', 'uint16']

to_match.each do |m|
  filter.add_param_to_match(m)
end

# Create a FunctionsWrapper which will sort our functions
sorter = Wrapper::FunctionsWrapper.new(wrapper.parser.getFunctions, filter)
sorter.sort

# Create a FunctionQualifier which will allow us
# to create generic rules to determine if a function is:
# void return function
# getter function (function which return value via pointer argument)
# getter array function (function that return an array)
# setter function
# setter array function

fq = Wrapper::FunctionQualifier.new
fq.is_void_instructions do |function|
  function.getReturn.getName.match(/void/)
end
#fq.is_getter_instructions do |function|
#  function.getName.match(/_get_/) ? true : false
#end
#fq.is_setter_instructions do |function|
#  !function.getName.match(/_get_/) ? true : false
#end
#fq.is_array_setter_instructions do |function|
#  function.getName.match(/vte_terminal_set_colors/) ? true : false
#end
#fq.is_array_getter_instructions do |_function|
#  false
#end
fq.is_getter_by_return_instructions do |function|
  test = true
  function.getParameters.each do |parameter|
    ptype = parameter.getType.getName
    if ptype.match(/\*/) && !ptype.match(/(GtkNotebook)|(char)/)
      test = false
    end
  end
  test
end
## Generate a code handler for simple fonction
# setter function that return value
wrapper = Wrapper::Rewritter.new
wrapper.rename_instructions do |name|
  "rtortosa_#{name.gsub('gtk_', '')}"
end
wrapper.wrapper_r_arguments_instructions do |parameter|
  type = parameter.getType.getName
  case
  when type =~ /GtkNotebook\s\*/
    'VALUE self'
  when type =~ /char\s+\*/
    "VALUE #{parameter.getName}"
  when type =~ /[^\*]+/
    "VALUE #{parameter.getName}"
  else
    ''
  end
end
# TODO notebook add handler for GTK_POSITION, uint16
wrapper.wrapper_r_2_c_instructions do |parameter|
  c_type = parameter.getType.getName
  r_name = parameter.getName
  c_name = 'c_' + r_name
  case
  when c_type =~ /(gint)|(GtkPositionType)/
    Wrapper.rb_num_2_int(r_name, c_type, c_name)
  when c_type =~ /.*char\s+\*/
    Wrapper.rb_str_2_c_char_ptr(r_name, c_type, c_name)
  when c_type == 'gboolean'
    Wrapper.rb_boolean_2_c_boolean(r_name, c_type, c_name)
  when c_type == 'gint *'
    Wrapper.c_pointer_arg_to_rb_value(r_name, c_type, c_name, 'int')
  when c_type == 'glong *'
    Wrapper.c_pointer_arg_to_rb_value(r_name, c_type, c_name, 'long')
  when c_type == 'glong'
    Wrapper.rb_num_2_long(r_name, c_type, c_name)
  when c_type == 'gdouble'
    Wrapper.rb_num_2_dbl(r_name, c_type, c_name)
  when c_type =~ /uint16/
    Wrapper.rb_num_2_uint16(r_name, c_type, c_name)
  when c_type =~ /GtkNotebook\s*\*/
    %{  notebook_t *n;
  Data_Get_Struct(self, notebook_t,n);
  GtkNotebook * notebook = GTK_NOTEBOOK(n->notebook);
}
  else
    ''
  end
end
wrapper.wrapper_c_arguments_instructions do |parameter|
  if parameter.getType.getName == 'GtkNotebook *'
    'notebook'
  else
    "c_#{parameter.getName}"
  end
end
wrapper.wrapper_r_return_instructions do |function|
  type = function.getReturn.getName
  if fq.is_getter_by_return(function)
    case
    when type =~ /(g)*int/
      '  return INT2FIX(ret);'
    when type =~ /.*char\s+\*/
      '  return rb_str_new2(ret);'
    when type == 'gboolean'
      '  return ret? Qtrue: Qfalse;'
    when type == 'void'
      '  return Qnil;'
    else
      ''
    end
  else
    s = '  VALUE ret= rb_ary_new();' + Wrapper::NEWLINE
    function.getParameters.each do |p|
      #      s += wrapper.wrapper_r_2_c(p)
      s += "  rb_ary_push(ret, #{p.getName});" + Wrapper::NEWLINE unless p.getType.getName =~ /GtkNotebook/
    end
    s += '  return ret;' + Wrapper::NEWLINE
    s
  end
end

# put it all together to write the handlers
def generate_setter_handler(f, wrapper, fq)
  s = 'static VALUE ' + wrapper.rename(f.getName) + Wrapper::O_BRACKET
  buff = []
  f.getParameters.each do |p|
    r_arg = wrapper.wrapper_r_arguments(p)
    buff << r_arg unless r_arg == ''
  end
  s += buff.join(Wrapper::COMMA)
  s +=  Wrapper::C_BRACKET + Wrapper::O_CURLY_BRACKET + Wrapper::NEWLINE
  f.getParameters.each do |p|
    s += wrapper.wrapper_r_2_c(p)
  end
  s += '  '
  s += "#{f.getReturn.getName} ret =" unless !fq.is_getter_by_return(f) || fq.is_void(f)
  s +=  f.getName + Wrapper::O_BRACKET
  buff.clear
  f.getParameters.each do |p|
    buff << wrapper.wrapper_c_arguments(p)
  end
  s += buff.join(Wrapper::COMMA) + Wrapper::C_BRACKET + Wrapper::SEMI_COLON + Wrapper::NEWLINE
  s +=  wrapper.wrapper_r_return(f)
  s += Wrapper::NEWLINE + Wrapper::C_CURLY_BRACKET
end

def print_function(f)
  puts "#{f.getReturn.getName} #{f.getName}(#{f.getParameters.map { |p|"#{p.getType.getName} #{p.getName}" }.join(',')})"
end

out = Wrapper::OutputFiles.new('notebook_test_methods')
out._h.puts(File.open('gtk_notebook_methods_h', 'rb') { |f| f.read })
out._c.puts(File.open('gtk_notebook_methods_c_1', 'rb') { |f| f.read })

lost = []
sorter.functions_to_parse.each do |f|
##  if (fq.is_setter(f) && !fq.is_array_setter(f)) || fq.is_getter(f)
    out._c.puts(generate_setter_handler(f, wrapper, fq))
##  else
    lost << f
##  end
end

out._c.puts(File.open('gtk_notebook_methods_c_2', 'rb') { |f| f.read })
def get_callback_parameters_number(params)
  nb = params.size
  params.each do |p|
    type = p.getType.getName
    case
    when type =~ /GtkNotebook/
      nb = nb - 1
    when type =~ /\*/ && !type =~ /char\s+\*/
      nb = nb - 1
    end
  end
  nb
end

sorter.functions_to_parse.each do |f|
  out._c.puts(%{  rb_define_method(c_vte,
                                        "#{f.getName.gsub('gtk_notebook_', '')}",
                                        RUBY_METHOD_FUNC(rtortosa_#{f.getName.gsub('gtk_', '')}),
                                        #{get_callback_parameters_number(f.getParameters)});} +
  Wrapper::NEWLINE)
end
out._c.puts(Wrapper::C_CURLY_BRACKET)

# write informations about handled functions and not handled
out._h.puts(<<INFOS)
/*|--------------------------------------->>*/
/* functions wrapped                        */
/*<<---------------------------------------|*/
INFOS
sorter.functions_to_parse.each { |f| out._h.puts('//' + f.getName) }
out._h.puts(<<INFOS)
/*|--------------------------------------->>*/
/* functions ignored                        */
/*<<---------------------------------------|*/
INFOS
sorter.functions_to_reject.each { |f| out._h.puts('//' + f.getName) }

out.close_all

# puts "Parsed : #{sorter.functions_to_parse.size}"
# puts "Losts: #{lost.size}"
# puts "Rejected: #{sorter.functions_to_reject.size}"
# lost.each do |f|
#  print_function(f)
# end
