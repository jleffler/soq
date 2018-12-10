#!/bin/sh
#
# Reformat some C code with decrust for presentation to SO

# Remove leading space so #include lines will be indented OK;
# using decrust deals with most of the rest; fixdbl adds blank
# lines between functions; stripdupblanklines carefully doesn't
# remove repeated lines of code; so indents for SO; and pbcopy
# captures the output for pasting back to SO.

sed 's/^[[:space:]]\{1,\}//' |
decrust |
fixdbl |
stripdupblanklines |
so |
pbcopy
