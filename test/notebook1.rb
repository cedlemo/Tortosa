#!/usr/bin/env ruby
require "../rtortosa"
Rtortosa::init(ARGV)
noto = Rtortosa::notebook
puts noto.class
Rtortosa::run
