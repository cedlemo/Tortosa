#!/usr/bin/env ruby
require "../rtortosa"

win = Rtortosa::init()
win::set_default_size(800, 400) 
win::background_color = Rtortosa::Color.new("#333333ff") 
cb = Proc.new{ |event, userdata|
  puts "-->userdata : #{userdata}"
  puts "-->event->time #{event[:time]}"
  puts "-->event->keyval #{event[:keyval]}"
  puts "-->event->state #{event[:state]}"
  puts "-->event->keyname #{event[:keyname]}"
  color = userdata::pick_a_color
  puts "color #{color.get_color} or #{color.get_rgb_color}"
  userdata::background_color = color
}
win::on_key_press_event({:key_event_cb => cb}, {:key_event_cb => win})
win::run
