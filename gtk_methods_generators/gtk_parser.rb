##
# Ruby module for writting Ruby code from C code that have been parsed by rtruckboris
module Wrapper
require 'rtruckboris'
  NEWLINE ="\n"
  O_BRACKET ="("
  C_BRACKET = ")"
  O_CURLY_BRACKET = "{"
  C_CURLY_BRACKET = "}"
  COMMA = ","
  SEMI_COLON = ";"

##
# Class that handle the rtruckboris parser and the source file
  class GlobalWrapper
    attr_reader :source, :headers_paths, :wrapper_c, :wrapper_h, :parser

    def initialize(source, headers_paths)
      @source = source
      init_headers_paths
      @headers_paths.push(*headers_paths)
      @parser = Rtruckboris::HeaderParser.new(@source, @headers_paths)
    end

    def parse(only_main_file)
      @parser.parse(only_main_file)
    end

    private

    def init_headers_paths
      @headers_paths = []
      gcc_lib_base='/usr/lib/gcc/' << `llvm-config --host-target`.chomp << '/*'
      gcc_lib = Dir.glob(gcc_lib_base ).sort.last + '/include'
      @headers_paths << gcc_lib
      @headers_paths << '/usr/include'
    end
  end
 
  class OutputFiles
    attr_reader :_c, :_h
    def initialize(name)
      @_c = File.new((name||'wrapper') + '.c', 'w')
      @_h = File.new((name||'wrapper') + '.h', 'w')
      @_c.sync= true
      @_c.sync= true
    end
    def close_all
      @_c.close
      @_h.close
    end
  end 
  class FunctionsWrapper
    attr_reader :functions, :functions_to_parse, :functions_to_reject, :filter
    def initialize(functions, filter)
      @functions = functions
      @filter = filter
    end
    def sort
      @functions.each do |f|
        if  !@filter.reject_on_name(f) &&
            !@filter.reject_on_params(f) &&
            !@filter.reject_on_not_match_params(f) &&
            !@filter.reject_on_return_type(f) &&
            !@filter.reject_on_not_match_return(f)
          (@functions_to_parse||@functions_to_parse=[]) << f
        else
          (@functions_to_reject||@functions_to_reject=[]) << f
        end 
      end
    end
  end
  
  class FunctionsFilter
    def add_name_to_reject(name)
      (@names_to_reject||@names_to_reject=[])<< name
    end
    def add_param_to_reject(param)
      (@params_to_reject||@params_to_reject=[])<< param
    end
    def add_param_to_match(param)
      (@params_to_exclusively_match||@params_to_exclusively_match=[])<< param
    end
    def add_return_type_to_match(return_type)
      (@return_types_to_exclusively_match||@return_types_to_exclusively_match=[]) << return_type
    end
    def add_return_type_to_reject(return_type)
      (@return_types_to_reject||@return_types_to_reject=[]) << return_type
    end
    def reject_on_name(function)
      return false if !@names_to_reject
      reg = "(" << @names_to_reject.join(")|(") << ")"
      function.getName =~ /#{reg}/
    end
    def reject_on_params(function)
      ret = false
      return ret if !@params_to_reject
      function.getParameters.each do |p|
        break if (ret = check_regexps(p.getType.getName,@params_to_reject))
      end
      ret
    end
    def reject_on_not_match_params(function)
      ret = false
      return ret if !@params_to_exclusively_match
      function.getParameters.each do |p|
        ret = true if !check_regexps(p.getType.getName, @params_to_exclusively_match)
      end
      ret
    end
    def reject_on_not_match_return(function)
      return false if !@return_types_to_exclusively_match
      !(check_regexps(function.getReturn.getName,@return_types_to_exclusively_match))
    end
    def reject_on_return_type(function)
      return false if !@return_types_to_reject
      check_regexps(function.getReturn.getName, @return_types_to_reject)
    end
    private
    def check_regexps(pattern, reg_array)
      reg = "(" << reg_array.join(")|(") << ")"
      pattern =~ /#{reg}/
    end
  end

  class FunctionQualifier
    patterns=[:is_void, :is_setter, :is_array_setter, :is_getter, :is_getter_by_return, :is_array_getter]
    patterns.each do |p|
      method_name = (p.to_s + '_instructions').to_sym
      define_method  method_name do |&block|
        instance_variable_set("@#{p.to_s + '_instructions'}", block)
      end
      define_method p do |arg|
        instance_variable_get("@#{p.to_s + '_instructions'}").call(arg)
      end
    end
  end
  class Rewritter
    patterns=[:rename,:wrapper_r_arguments,:wrapper_r_2_c, :wrapper_c_2_r, :wrapper_c_arguments,:wrapper_r_return, :function_is_argument_modifier]
    patterns.each do |p|
      method = (p.to_s + '_instructions').to_sym
      define_method  method do |&block|
        instance_variable_set("@#{p.to_s + '_instructions'}", block)
      end
      define_method p do |arg|
        instance_variable_get("@#{p.to_s + '_instructions'}").call(arg)
      end
    end
  end
  ##
  # When wrapping c functions to ruby, those methods convert ruby arguments of the wrapper 
  # to c arguments for the c function wrapped.
  # For example, this function : void myfunction(int a, int b);
  # will be wrapped like this with Rewritter.rename and Rewritter.wrapper_r_arguments:
  # static VALUE rb_myfunction(VALUE a, VALUE b) then
  # for each argument of myfunction, Wrapper.rb_num_2_int(r_name,c_type,c_name)
  # will be called like this Wrapper.rb_num_2_int("a", "int", "c_name")
  # and generate this code:
  # static VALUE rb_myfunction(VALUE a, VALUE b) {
  #  if(TYPE(a) != T_FIXNUM)
  #    rb_raise(rb_eTypeError, "invalid type for input");
  #  int c_a = FIX2INT(a);
  #  if(TYPE(b) != T_FIXNUM)
  #    rb_raise(rb_eTypeError, "invalid type for input");
  #  int c_b = FIX2INT(b);
  # Rewritter.wrapper_r_return and Rewritter.wrapper_c_arguments will generate this:
  #  my_function(c_a, c_b);
  #  return Qnil;
  # }
  def self.rb_str_2_c_char_ptr(r_val_name, c_val_type, c_val_name)
        %Q{  if(TYPE(#{r_val_name}) != T_STRING)
    rb_raise(rb_eTypeError, "invalid type for input");
  #{c_val_type} #{c_val_name}=RSTRING_PTR(#{r_val_name});
}
  end
  def self.rb_boolean_2_c_boolean(r_val_name, c_val_type, c_val_name)
        %Q{  #{c_val_type} #{c_val_name}= (#{r_val_name} == Qtrue) ? TRUE : FALSE;
}
  end
  def self.rb_num_2_int8(r_val_name, c_val_type, c_val_name)
    %Q{  #{c_val_type} #{c_val_name};
  if (TYPE(#{r_val_name}) == T_FIXNUM)
    #{c_val_name}=int2int8(FIX2INT(#{r_val_name}));
  else if(TYPE(TYPE(#{r_val_name}) == T_BIGNUM))
    #{c_val_name}=int2int8(NUM2INT(#{r_val_name}));
  else
    rb_raise(rb_eTypeError, "invalid type for input");
}
  end
  def self.rb_num_2_uint8(r_val_name, c_val_type, c_val_name)
    %Q{  #{c_val_type} #{c_val_name};
  if (TYPE(#{r_val_name}) == T_FIXNUM)
    #{c_val_name}=int2uint8FIX2UINT(#{r_val_name}));
  else if(TYPE(TYPE(#{r_val_name}) == T_BIGNUM))
    #{c_val_name}=int2uint8(NUM2UINT(#{r_val_name}));
  else
    rb_raise(rb_eTypeError, "invalid type for input");
}
  end
  def self.rb_num_2_int16(r_val_name, c_val_type, c_val_name)
    %Q{  #{c_val_type} #{c_val_name};
  if (TYPE(#{r_val_name}) == T_FIXNUM)
    #{c_val_name}=int2int16(FIX2INT(#{r_val_name}));
  else if(TYPE(TYPE(#{r_val_name}) == T_BIGNUM))
    #{c_val_name}=int2int16(NUM2INT(#{r_val_name}));
  else
    rb_raise(rb_eTypeError, "invalid type for input");
}
  end
  def self.rb_num_2_uint16(r_val_name, c_val_type, c_val_name)
    %Q{  #{c_val_type} #{c_val_name};
  if (TYPE(#{r_val_name}) == T_FIXNUM)
    #{c_val_name}=int2uint16FIX2UINT(#{r_val_name}));
  else if(TYPE(TYPE(#{r_val_name}) == T_BIGNUM))
    #{c_val_name}=int2uint16(NUM2UINT(#{r_val_name}));
  else
    rb_raise(rb_eTypeError, "invalid type for input");
}
  end
  def self.rb_num_2_int32(r_val_name, c_val_type, c_val_name)
    %Q{  #{c_val_type} #{c_val_name};
  if (TYPE(#{r_val_name}) == T_FIXNUM)
    #{c_val_name}=int2int32(FIX2INT(#{r_val_name}));
  else if(TYPE(TYPE(#{r_val_name}) == T_BIGNUM))
    #{c_val_name}=int2int32(NUM2INT(#{r_val_name}));
  else
    rb_raise(rb_eTypeError, "invalid type for input");
}
  end
  def self.rb_num_2_uint32(r_val_name, c_val_type, c_val_name)
    %Q{  #{c_val_type} #{c_val_name};
  if (TYPE(#{r_val_name}) == T_FIXNUM)
    #{c_val_name}=int2uint32FIX2UINT(#{r_val_name}));
  else if(TYPE(TYPE(#{r_val_name}) == T_BIGNUM))
    #{c_val_name}=int2uint32(NUM2UINT(#{r_val_name}));
  else
    rb_raise(rb_eTypeError, "invalid type for input");
}
  end
  def self.rb_num_2_int(r_val_name, c_val_type, c_val_name)
    %Q{  #{c_val_type} #{c_val_name};
  if (TYPE(#{r_val_name}) == T_FIXNUM)
    #{c_val_name}=FIX2INT(#{r_val_name});
  else if(TYPE(TYPE(#{r_val_name}) == T_BIGNUM))
    #{c_val_name}=NUM2INT(#{r_val_name});
  else
    rb_raise(rb_eTypeError, "invalid type for input");
}
  end
  def self.rb_num_2_uint(r_val_name, c_val_type, c_val_name)
    %Q{    #{c_val_type} #{c_val_name};
  if (TYPE(#{r_val_name}) == T_FIXNUM)
    #{c_val_name}=FIX2UINT(#{r_val_name});
  else if(TYPE(TYPE(#{r_val_name}) == T_BIGNUM))
    #{c_val_name}=NUM2UINT(#{r_val_name});
  else
    rb_raise(rb_eTypeError, "invalid type for input");
}
  end
  def self.rb_num_2_long(r_val_name, c_val_type, c_val_name)
    %Q{  #{c_val_type} #{c_val_name};
  if (TYPE(#{r_val_name}) == T_FIXNUM)
    #{c_val_name}=FIX2LONG(#{r_val_name});
  else if(TYPE(TYPE(#{r_val_name}) == T_BIGNUM))
    #{c_val_name}=NUM2LONG(#{r_val_name});
  else
    rb_raise(rb_eTypeError, "invalid type for input");
}
  end
  def self.rb_num_2_ulong(r_val_name, c_val_type, c_val_name)
    %Q{   #{c_val_type} #{c_val_name};
   if (TYPE(#{r_val_name}) == T_FIXNUM)
    #{c_val_name}=FIX2ULONG(#{r_val_name});
  else if(TYPE(TYPE(#{r_val_name}) == T_BIGNUM))
    #{c_val_name}=NUM2ULONG(#{r_val_name});
  else
    rb_raise(rb_eTypeError, "invalid type for input");
}
  end
  def self.rb_num_2_short(r_val_name, c_val_type, c_val_name)
    %Q{    #{c_val_type} #{c_val_name};
    if (TYPE(#{r_val_name}) == T_FIXNUM)
    #{c_val_name}=FIX2SHORT(#{r_val_name});
  else if(TYPE(TYPE(#{r_val_name}) == T_BIGNUM))
    #{c_val_name}=NUM2SHORT(#{r_val_name});
  else
    rb_raise(rb_eTypeError, "invalid type for input");
}
  end
  def self.rb_num_2_ushort(r_val_name, c_val_type, c_val_name)
    %Q{    #{c_val_type} #{c_val_name};
  if (TYPE(#{r_val_name}) == T_FIXNUM)
    #{c_val_name}=rb_fix2ushort(#{r_val_name});
  else if(TYPE(TYPE(#{r_val_name}) == T_BIGNUM))
    #{c_val_name}=NUM2USHORT(#{r_val_name});
  else
    rb_raise(rb_eTypeError, "invalid type for input");
}
  end
  def self.rb_num_2_llong(r_val_name, c_val_type, c_val_name)
    %Q{  if (TYPE(#{r_val_name}) != T_FIXNUM) && (TYPE(#{r_val_name}) != T_BIGNUM)
  rb_raise(rb_eTypeError, "invalid type for input");
    #{c_val_type} #{c_val_name}=NUM2LL(#{r_val_name});
}
  end
  def self.rb_num_2_ullong(r_val_name, c_val_type, c_val_name)
    %Q{  if (TYPE(#{r_val_name}) != T_FIXNUM) && (TYPE(#{r_val_name}) != T_BIGNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  #{c_val_type} #{c_val_name}=NUM2ULL(#{r_val_name});
}
  end
  def self.rb_num_2_dbl(r_val_name, c_val_type, c_val_name)
    %Q{  if ((TYPE(#{r_val_name}) != T_FIXNUM) && (TYPE(#{r_val_name}) != T_BIGNUM))
    rb_raise(rb_eTypeError, "invalid type for input");
  #{c_val_type} #{c_val_name}=NUM2DBL(#{r_val_name});
}
  end
  def self.rb_num_2_sizet(r_val_name, c_val_type, c_val_name)
    %Q{  if (TYPE(#{r_val_name}) != T_FIXNUM) && (TYPE(#{r_val_name}) != T_BIGNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  #{c_val_type} #{c_val_name}=NUMSIZET(#{r_val_name});
}
  end
  def self.rb_num_2_ssizet(r_val_name, c_val_type, c_val_name)
    %Q{  if (TYPE(#{r_val_name}) != T_FIXNUM) && (TYPE(#{r_val_name}) != T_BIGNUM)
    rb_raise(rb_eTypeError, "invalid type for input");
  #{c_val_type} #{c_val_name}=NUMSSIZET(#{r_val_name});
}
  end
  def self.c_char_ptr_2_rb_str(r_val_name, c_val_name)
    %Q{  VALUE #{r_val_name} = rb_str_new2(#{c_val_name});
}
  end
  def self.c_boolean_2_rb_boolean(r_val_name, c_val_name)
    %Q{  VALUE #{r_val_name} = #{c_val_name} == TRUE ? Qtrue : Qfalse;
}
  end
  def self.c_int_2_rb_num(r_val_name, c_val_name)
    %Q{  VALUE #{r_val_name} = INT2NUM((int) #{c_val_name});
}
  end  
  def self.c_uint_2_rb_num(r_val_name, c_val_name)
    %Q{  VALUE #{r_val_name} = UINT2NUM((int) #{c_val_name});
}
  end
  def self.c_long_2_rb_num(r_val_name, c_val_name)
    %Q{  VALUE #{r_val_name} = LONG2NUM(#{c_val_name});
}
  end
  def self.c_ulong_2_rb_num(r_val_name, c_val_name)
    %Q{  VALUE #{r_val_name} = ULONG2NUM(#{c_val_name});
}
  end
  def self.c_llong_2_rb_num(r_val_name, c_val_name)
    %Q{  VALUE #{r_val_name} = LL2NUM(#{c_val_name});
}
  end
  def self.c_ullong_2_rb_num(r_val_name, c_val_name)
    %Q{  VALUE #{r_val_name} = ULL2NUM(#{c_val_name});
}
  end
  def self.c_dbl_2_rb_num(r_val_name, c_val_name)
    %Q{  VALUE #{r_val_name} = DBL2NUM(#{c_val_name});
}
  end
  def self.c_sizet_2_rb_num(r_val_name, c_val_name)
    %Q{  VALUE #{r_val_name} = SIZET2NUM(#{c_val_name});
}
  end
  def self.c_ssizet_2_rb_num(r_val_name, c_val_name)
    %Q{  VALUE #{r_val_name} = SSIZET2NUM(#{c_val_name});
}
  end
  def self.c_pointer_arg_to_rb_value(r_val_name, c_val_type, c_val_name, type)
    local_type = c_val_type.gsub(/\s*\*\s*/,"")
    local_var = "local_" + c_val_name
    #s = Wrapper::send("c_#{type}_2_rb_num".to_sym, r_val_name,local_var)
    s = "  #{local_type} #{local_var};" + NEWLINE
    s += "  #{c_val_type} #{c_val_name} = &#{local_var};" + NEWLINE
  end


  def self.rb_simple_class_to_c(r_val_name, c_val_name, class_name, module_name, structure)
     %Q{  VALUE m_#{module_name} = rb_const_get( rb_cObject, rb_intern( "#{module_name}" ));
  VALUE c_#{class_name} = rb_const_get_at( m_#{module_name}, rb_intern("#{class_name}") );
  if(rb_class_of(#{r_val_name}) != c_#{class_name})
    rb_raise(rb_eTypeError, "invalid type for input");
  #{structure} *#{c_val_name};
  Data_Get_Struct(#{r_val_name}, #{structure},#{c_val_name});
}   
  end
  ##
  # Used when one want to get the data structure of the class and add precision on
  # how to transform the ptr, called structure name + "_ptr", to the c argument
  def self.rb_custom_class_to_c(arg_name,class_name, module_name, structure, precision)
    struct_ptr_name = structure + "_ptr"
    %Q{  VALUE m_#{module_name} = rb_const_get( rb_cObject, rb_intern( "#{module_name}" ));
  VALUE c_#{class_name} = rb_const_get_at( m_#{module_name}, rb_intern("#{class_name}") );
  if(rb_class_of(#{arg_name}) != c_#{class_name})
    rb_raise(rb_eTypeError, "invalid type for input");
  #{structure} *#{struct_ptr_name};
  Data_Get_Struct(#{arg_name}, #{structure},#{struct_ptr_name});
} + precision
  end
  def self.generate_simple_class_allocator(name)
%Q{ /*#{name} ruby class*/
#include "gtk_#{name}_methods.h"

static void c_#{name}_struct_free(#{name}_t *c)
{
  if(c)
  {
    ruby_xfree(c);
  }
}
static VALUE c_#{name}_struct_alloc( VALUE klass)
{
  return Data_Wrap_Struct(klass, NULL, c_#{name}_struct_free, ruby_xmalloc(sizeof(#{name}_t)));
}
/*static VALUE c_#{name}_initialize(VALUE self)
{
}*/} 
  end
  def self.generate_wrapped_sumup(functions_sorted)
s= <<INFOS 
/*|--------------------------------------->>*/
/* functions wrapped                        */
/*<<---------------------------------------|*/
INFOS
functions_sorted.functions_to_parse.each { |f| s= s + '//' + f.getName + NEWLINE}
s+=<<INFOS
/*|--------------------------------------->>*/
/* functions ignored                        */
/*<<---------------------------------------|*/
INFOS
#functions_sorted.functions_to_reject.each { |f| puts f.class }#s= s+ '//' + f.getName + NEWLINE}}
#functions_sorted.functions_to_reject.each { |f| puts f.class ;puts f.methods}#s= s+ '//' + f.getName + NEWLINE}}
#functions_sorted.functions_to_reject.each_with_index { |f,i| puts f.getName + " " + i.to_s}
functions_sorted.functions_to_reject.each { |f| s= s+ '//' + f.getName + NEWLINE}
#functions_sorted.functions_to_reject.each_with_index do |f, index| 
#   s= s+ '//' + f.getName + NEWLINE
#  puts index
#end
#functions_sorted.functions_to_reject.each { |f| s= s+ '//' + f.getParameters.size.to_s + NEWLINE}
  s
  end
end
