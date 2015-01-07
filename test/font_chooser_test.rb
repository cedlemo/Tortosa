#!/usr/bin/env ruby
require "../rtortosa"

win = Rtortosa::init(ARGV)
win::set_default_size(800, 400) 
win::background_color = Rtortosa::Color.new("#333333ff") 
cb = Proc.new{ |event, userdata|
  puts "-->userdata : #{userdata}"
  puts "-->event->time #{event[:time]}"
  puts "-->event->keyval #{event[:keyval]}"
  puts "-->event->state #{event[:state]}"
  puts "-->event->keyname #{event[:keyname]}"
  font = userdata::pick_a_font || Rtortosa::Font.new("Droid sans 10")
  puts "font #{font.to_s}"
}
win::on_key_press_event(cb, win)
win::run
