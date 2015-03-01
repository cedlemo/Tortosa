#!/usr/bin/env ruby
require "../rtortosa"

win = Rtortosa::init(ARGV)
win = Rtortosa.window
win.set_default_size(800, 600) 
Rtortosa::background_color = Rtortosa::Color.new("#333333ff") 
first_vte = Rtortosa::Vte.new
first_vte.spawn("/bin/fish")
first_vte.set_rewrap_on_resize(true)
Rtortosa::run
