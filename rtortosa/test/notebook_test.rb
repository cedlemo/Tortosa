#!/usr/bin/env ruby
require "../rtortosa"
ARGV.each do |a|
  puts a
end
win = Rtortosa::init(ARGV)
win::set_default_size(800, 800)
win::set_title('Rtortosa')
win::set_role('Rtortosa')
win::set_wmclass('Rtortosa','Rtortosa')
win::set_icon_name('terminal')
win::background_color = Rtortosa::Color.new("#333333ff") 
win::notebook_set_tab_pos(Rtortosa::POS_BOTTOM)
command_cb = Proc.new{ |command, userdata| 
  puts "command line: #{command}"
#  puts "-->userdata : #{userdata}"
#  puts "-->event->time #{event[:time]}"
#  puts "-->event->keyval #{event[:keyval]}"
#  puts "-->event->state #{event[:state]}"
#  puts "-->event->keyname #{event[:keyname]}"
  case command
  when 'set background'
    userdata::background_color = userdata::pick_a_color || Rtortosa::Color.new("#33333355")
  when 'no border'
    userdata::set_decorated(false)
  when 'with border'
    userdata::set_decorated(true)
  when 'quit'
    userdata::quit
  else
    puts "Unknow command : #{command}"
  end
}
win::on_command_line_event( command_cb,  win)
win::run
