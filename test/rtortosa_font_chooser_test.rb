#!/usr/bin/env ruby
require "../rtortosa"

Rtortosa::init(ARGV)
win = Rtortosa::window
win.set_default_size(800, 400) 
Rtortosa.background_color = Rtortosa::Color.new("#333333ff") 
cb = Proc.new{ |event, userdata|
  puts "-->userdata : #{userdata}"
  puts "-->event->time #{event[:time]}"
  puts "-->event->keyval #{event[:keyval]}"
  puts "-->event->state #{event[:state]}"
  puts "-->event->keyname #{event[:keyname]}"
  font = Rtortosa::pick_a_font || Rtortosa::Font.new("Droid sans 10")
  puts "font #{font.to_s}"
}
Rtortosa::on_key_press_event(cb, "anything you want")
Rtortosa::run
