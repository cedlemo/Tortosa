#!/usr/bin/env ruby
require "../rtortosa"

win = Rtortosa::init(ARGV)
win::set_default_size(800, 600) 
win::background_color = Rtortosa::Color.new("#333333ff") 
Rtortosa::Vte.new("/bin/fish")
win::run
