#!/bin/sh
#
# Convert suitably laid out data into a boxed table
#
# The suitable layout is an arbitrary number of blocks of data, where
# each block consists of one line per field.
# The blocks should have a uniform number of entries.
# There can be multiple blank lines, and fields can start or end with
# stray white space, which will be removed, and with multiple spaces
# within a field which will be normalized to single spaces.
# Comment lines start with a hash `#` and are ignored.
# This normalization is controlled by tab-normal.sh.
#
# The table is then layed out with Unicode box characters.  It should
# present tidily in constant width font.  The first block of data is
# treated as column headings and is separated from the other lines.
# There is no maximum width for the table or fields.
# Data is right justified; there's no way to left justify it yet.
#
# See tab-example.1 and tab-example.2 for illustrations.

sh tab-normal.sh "$@" | awk -f fmt-tabulate.awk
