#!/usr/bin/env ruby
require "../rtortosa"

Rtortosa::init(ARGV)
win = Rtortosa.window
win.set_default_size(800, 400) 
Rtortosa.background_color = Rtortosa::Color.new("#333333ff") 
cb = Proc.new{ |event, win|
  puts "-->userdata : #{win.class}"
  puts "-->event->time #{event[:time]}"
  puts "-->event->keyval #{event[:keyval]}"
  puts "-->event->state #{event[:state]}"
  puts "-->event->keyname #{event[:keyname]}"
  color = Rtortosa::pick_a_color || Rtortosa::Color.new("#33ff3344")
  puts "color #{color.get_hex_color} or #{color.get_rgb_color}"
  Rtortosa::background_color = color
}
Rtortosa::on_key_press_event(cb, win)
Rtortosa::run
