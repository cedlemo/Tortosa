#!/usr/bin/env ruby

require File.dirname(__FILE__) + "/parser"

gtk_window = "/usr/include/gtk-3.0/gtk/gtkwindow.h"
headerPaths = `pkg-config --cflags gtk+-3.0`.gsub("-I","").split(" ")
#get gcc include if needed
gccLibBase='/usr/lib/gcc/' << `llvm-config --host-target`.chomp << "/*"
gccLib = Dir.glob(gccLibBase ).sort.last + "/include"
headerPaths << gccLib
headerPaths << "/usr/include"

parser = Parser::HeaderParser.new(gtk_window, headerPaths)
parser.parse(true)

main_functions = parser.getFunctions()
puts "Functions number : #{main_functions.size}"
#functions.each do |f|
#  puts "Name : #{f.getName}"
#  puts "Return : #{f.getReturn.getName}"
#  params = f.getParameters
#  puts "\t #{params.size.to_s} parameters :"
#  params.each do |p|
#    puts "\t\t#{p.getType.getName}  #{p.getName}"
#  end
#end
boolean_setter_functions = []
boolean_getter_functions= []
functions = main_functions.clone
functions.each do |f|
  params = f.getParameters
end
functions.each do |f|
  params = f.getParameters
  if params.size == 1 && params[0].getType.getName == "GtkWindow *" && f.getReturn.getName == "gboolean"
    boolean_getter_functions << f
  end
  if params.size == 2 && params[0].getType.getName == "GtkWindow *" && params[1].getType.getName == "gboolean"
    boolean_setter_functions << f
  end
end
puts "Setter : #{boolean_setter_functions.size}"
boolean_setter_functions.each do |f| 
  puts f.getName
end
puts "Getter : #{boolean_getter_functions.size}"
boolean_getter_functions.each do |f| 
  puts f.getName
end
def write_boolean_setter_wrapper( f)
  puts %Q{VALUE rtortosa_#{f.getName.gsub("gtk_window_","")}( VALUE b){
    if(b == Qtrue )
      #{f.getName}(backbone.window.widget, TRUE);
    if(b == Qfalse)
      #{f.getName}(backbone.window.widget, FALSE);  
  }}
end
def write_boolean_getter_wrapper(f)
  puts %Q{VALUE rtortosa_#{f.getName.gsub("gtk_window_","")}( VALUE b){
    gboolean res =  #{f.getName}(backbone.window.widget);
    return res? Qtrue: Qfalse;
  }}

end
boolean_setter_functions.each do |f|
  write_boolean_setter_wrapper(f)
end
boolean_getter_functions.each do |f|
  write_boolean_getter_wrapper(f)
end
puts functions.size
