#!/usr/bin/env ruby
require "../rtortosa"

win = Rtortosa::init()
win::height = 100 
win::width = 800
win::background_color = Rtortosa::Color.new("#333333ff") 
win::run
