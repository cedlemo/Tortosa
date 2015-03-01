#!/usr/bin/env ruby
require "../rtortosa"
ARGV.each do |a|
  puts a
end
Rtortosa::init(ARGV)
win = Rtortosa.window
win::set_default_size(800, 800)
win::set_title('Rtortosa')
win::set_role('Rtortosa')
win::set_wmclass('Rtortosa','Rtortosa')
win::set_icon_name('terminal')
Rtortosa.background_color = Rtortosa::Color.new("#333333ff") 
key_cb = Proc.new{ |event, userdata|
#  puts "-->userdata : #{userdata}"
#  puts "-->event->time #{event[:time]}"
#  puts "-->event->keyval #{event[:keyval]}"
#  puts "-->event->state #{event[:state]}"
#  puts "-->event->keyname #{event[:keyname]}"
}
command_cb = Proc.new{ |command, win| 
  puts "command line: #{command}"
#  puts "-->userdata : #{userdata}"
#  puts "-->event->time #{event[:time]}"
#  puts "-->event->keyval #{event[:keyval]}"
#  puts "-->event->state #{event[:state]}"
#  puts "-->event->keyname #{event[:keyname]}"
  case command
  when 'set background'
    Rtortosa::background_color = Rtortosa::pick_a_color || Rtortosa::Color.new("#33333355")
  when 'no border'
    win.set_decorated(false)
  when 'with border'
    win.set_decorated(true)
  when 'quit'
    Rtortosa.quit
  else
    puts "Unknow command : #{command}"
  end
}
##win::on_key_press_event( nil, nil)
Rtortosa::on_command_line_event( command_cb,  win)
Rtortosa.run
