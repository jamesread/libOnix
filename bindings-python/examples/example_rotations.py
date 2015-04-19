#!/usr/bin/python
import pyonix

w = 5; h = 5;
ox = w / 2; oy = h /2;
deg = 180

surface = pyonix.Surface(w, h, ".")
surface.set(0, 0, '1')
surface.set(w-1, 0, '2')
surface.set(0, h-1, '3')
surface.set(w-1, h-1, '4')
surface.set(ox, oy, '+')

print "Rotating around: %d:%d by %d" % (ox, oy, deg) + "\n"

print "Original (%dx%d):\n" % (w, h), str(surface) + "\n"
surface.rotate(ox, oy, deg, '.')
print "Rotated  (%dx%d):\n" % (w, h), str(surface)
