#!/usr/bin/python

import pyonix

surface = pyonix.Surface(11, 8, ' ')

# H
surface.vline(2, 2, 5, '#')
surface.vline(5, 2, 5, '#')
surface.hline(3, 4, 2, '=')

# I
surface.vline(8, 4, 3, '*')
surface.set(8, 3, '@')

surface.border()

print surface
