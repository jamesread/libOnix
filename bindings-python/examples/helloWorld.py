#!/usr/bin/python
import pyonix

surface = pyonix.Surface(16, 5, '.')
surface.border('|', '-', '+');
surface.text(2, 2, "Hello World!")

print surface

