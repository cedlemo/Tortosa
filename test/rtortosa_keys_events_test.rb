#!/usr/bin/env ruby
require "../rtortosa"

Rtortosa::init(ARGV)
win = Rtortosa::window
win::set_default_size(400,800)
Rtortosa::background_color = Rtortosa::Color.new("#333333ff") 
cb = Proc.new{ |event, userdata|
  puts "-->userdata : #{userdata}"
  puts "-->event->time #{event[:time]}"
  puts "-->event->keyval #{event[:keyval]}"
  puts "-->event->state #{event[:state]}"
  puts "-->event->keyname #{event[:keyname]}"
}
Rtortosa::on_key_press_event( cb, "What you want")
Rtortosa::run
