#!/usr/bin/env ruby
require "../rtortosa"
ARGV.each do |a|
  puts a
end
win = Rtortosa::init(ARGV)
win.set_default_size(800, 800)
win.set_title('Rtortosa')
win.set_role('Rtortosa')
win.set_wmclass('Rtortosa','Rtortosa')
win.set_icon_name('terminal')
win.background_color = Rtortosa::Color.new("#333333ff") 
win.notebook_set_tab_pos(Rtortosa::POS_BOTTOM)
vte = win.new_tab("/bin/zsh")
vte.set_color_background(Rtortosa::Color.new("#33333399"))
command_cb = Proc.new{ |win, command| 
  puts "command line: #{command}"
#  puts "-->userdata : #{userdata}"
#  puts "-->event->time #{event[:time]}"
#  puts "-->event->keyval #{event[:keyval]}"
#  puts "-->event->state #{event[:state]}"
#  puts "-->event->keyname #{event[:keyname]}"
  case command
  when 'set background'
    win.background_color = win.pick_a_color || Rtortosa::Color.new("#33333355")
  when 'no border'
    win.set_decorated(false)
  when 'with border'
    win.set_decorated(true)
  when 'quit'
    win.quit
  when 'bash'
    win.new_tab('/usr/bin/bash')
  else
    puts "Unknow command : #{command}"
    if command =~ /new\s+tab\s+(?<args>\w+)/
      puts Regexp.last_match[1] 
      win.new_tab(Regexp.last_match[1])
    end
  end
}
win.on_command_line_event( command_cb,  nil)
win.run
