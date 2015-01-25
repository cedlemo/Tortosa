#!/usr/bin/env ruby
require "../rtortosa"
ARGV.each do |a|
  puts a
end
Rtortosa::init(ARGV)
win = Rtortosa.window
win.set_default_size(800, 800)
win.set_title('Rtortosa try Notebook object')
win.set_role('Rtortosa')
win.set_wmclass('Rtortosa','Rtortosa')
win.set_icon_name('terminal')
Rtortosa.background_color = Rtortosa::Color.new("#333333ff") 
notebook = Rtortosa.notebook
notebook.show
win.show_all
notebook.set_tab_pos(Rtortosa::POS_BOTTOM)#Rtortosa::POS_BOTTOM)
command_cb = Proc.new{ |command, notebook| 
  puts "command line: #{command}"
  case command
  when 'no border'
    notebook.set_show_border(false)
  when 'with border'
    notebook.set_show_border(true)
  when 'show tabs'
    notebook.set_show_tabs(true)
  when 'hide tabs'
    notebook.set_show_tabs(false)
  else
    puts "Unknow command : #{command}"
  end
}
Rtortosa::on_command_line_event( command_cb,  notebook)
Rtortosa::run
