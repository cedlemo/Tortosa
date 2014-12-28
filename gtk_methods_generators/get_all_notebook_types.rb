#!/usr/bin/env ruby
require './gtk_parser'
# Parse the source files and get the functions all
source = '/usr/include/gtk-3.0/gtk/gtknotebook.h'
hp = `pkg-config --cflags gtk+-3.0`.gsub('-I', '').split(' ')
wrapper = Wrapper::GlobalWrapper.new(source, hp)
wrapper.parse(true)

args_types=[]
return_types=[]

wrapper.parser.getFunctions.each do |f|
  f.getParameters.each do |p|
    args_types << p.getType.getName unless args_types.include?(p.getType.getName)
  end
  return_types << f.getReturn.getName unless return_types.include?(f.getReturn.getName)
end

puts "All types:"

(args_types + return_types).uniq.each do |e|
  puts "*  " + e
end
puts "Arguments types"
args_types.each do |a|
  puts "-  " + a
end

puts "Return types"
return_types.each do |r|
  puts "+  " + r
end
