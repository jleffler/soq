import re
import fileinput

p1 = re.compile(r'\s*(\S[^&]*?)\s+(?:&|$)')

for line in fileinput.input():
    matches = p1.findall(line)
    print "Line: ", line
    for match in matches:
        print "Match: ", match
    print ""

