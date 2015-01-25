#!/usr/bin/env ruby
require "../rtortosa"

Rtortosa::init(ARGV)
#Rtortosa::Window.new()
win = Rtortosa::window
win.set_default_size(800, 100) 
win.set_title("Window 1 test")
win.set_wmclass("Simple Window","Simple tests")
sizes = win.get_size
puts sizes.class
puts "ok" if sizes[0] == 800
puts "ok" if sizes[1] == 100
positions = win.get_position
puts positions[0]
puts positions[1]
win.show_all #method herited from Widget class
puts "testing parse_geometry method, type enter when ready"
gets
puts win.parse_geometry("250x650-0+100")
Rtortosa::run
