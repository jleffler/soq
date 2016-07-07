#!/usr/bin/env python

import fileinput

d = {}

for line in fileinput.input():
    line = line.rstrip('\r\n') # line.strip() for leading and trailing space
    if line.startswith('Clutch'):
        key = line
        d[key] = ''
        pad = ''
    else:
        d[key] += pad + line
        pad = ', '

print d

for key in d:
    print "'%s': '%s'" % (key, d[key])
