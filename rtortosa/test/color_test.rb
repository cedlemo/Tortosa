#!/usr/bin/env ruby
require "../rtortosa"

c = Rtortosa::Color.new("#333333")
puts c.get_color
puts c.get_rgb_color
puts "red : #{c.get_red} -> #{255 * c.get_red}"
puts "green : #{c.get_green} -> #{255 * c.get_green}"
puts "blue : #{c.get_blue} -> #{255 * c.get_blue}"
puts "alpha : #{c.get_alpha} -> #{255 * c.get_alpha}"

#win = Rtortosa::init()
#win::height = 1
#win::width = 800
#win::run
