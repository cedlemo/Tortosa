#!/usr/bin/env ruby
require "../rtortosa"

Rtortosa::init(ARGV)
#Rtortosa::Window.new()
Rtortosa::window
#win::set_default_size(800, 100) 
#win::background_color = Rtortosa::Color.new("#333333ff") 
Rtortosa::run
