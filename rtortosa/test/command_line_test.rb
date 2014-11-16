#!/usr/bin/env ruby
require "../rtortosa"

win = Rtortosa::init()
win::set_default_size(800, 800)
win::set_title('Rtortosa')
win::set_role('Rtortosa')
win::set_wmclass('Rtortosa','Rtortosa')
win::set_icon_name('terminal')
win::background_color = Rtortosa::Color.new("#333333ff") 
key_cb = Proc.new{ |event, userdata|
#  puts "-->userdata : #{userdata}"
#  puts "-->event->time #{event[:time]}"
#  puts "-->event->keyval #{event[:keyval]}"
#  puts "-->event->state #{event[:state]}"
#  puts "-->event->keyname #{event[:keyname]}"
}
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
  else
    puts "Unknow command : #{command}"
  end
}
win::on_key_press_event( nil, nil)
win::on_command_line_event( command_cb,  win)
win::run
