#!/usr/bin/env ruby
require "../rtortosa"

win = Rtortosa::init()
win::height = 400 
win::width = 800
win::background_color = Rtortosa::Color.new("#333333ff") 
#key_cb = Proc.new{ |event, userdata|
#  puts "-->userdata : #{userdata}"
#  puts "-->event->time #{event[:time]}"
#  puts "-->event->keyval #{event[:keyval]}"
#  puts "-->event->state #{event[:state]}"
#  puts "-->event->keyname #{event[:keyname]}"
#}
def set_background()
  
end
command_cb = Proc.new{ |command, event, userdata| 
  puts "command line: #{command}"
#  puts "-->userdata : #{userdata}"
#  puts "-->event->time #{event[:time]}"
#  puts "-->event->keyval #{event[:keyval]}"
#  puts "-->event->state #{event[:state]}"
#  puts "-->event->keyname #{event[:keyname]}"

  if command == "set background"
    userdata::background_color = userdata::pick_a_color || Rtortosa::Color.new("#33333355")
  else
    puts "Unknow command : #{command}"
  end
}
win::on_key_press_event({:command_line_cb => command_cb}, { :command_line_cb=>win})
win::run
