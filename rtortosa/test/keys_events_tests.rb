#!/usr/bin/env ruby
require "../rtortosa"

win = Rtortosa::init()
win::set_default_size(400,800)
win::background_color = Rtortosa::Color.new("#333333ff") 
cb = Proc.new{ |event, userdata|
  puts "-->userdata : #{userdata}"
  puts "-->event->time #{event[:time]}"
  puts "-->event->keyval #{event[:keyval]}"
  puts "-->event->state #{event[:state]}"
  puts "-->event->keyname #{event[:keyname]}"
}
win::on_key_press_event( cb, "key")
win::run
