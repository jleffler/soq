#!/bin/sh

# Test file for check-references.sh

### test1.c

### test2.h

### test2.h

# That's two of test2.h - it should be reported as a duplicate

### test-3.c

### test-4.c

### file3.h

### Warning

# The warning mustn't produce a warning.

# Test command:

set -x
bash check-references.sh $0 test1.c test2.h test-3.c test-5.c test4.c

# Should produce complaints about:

# -- test2.h and file3.h being repeated.
# -- test2.h, test4.h and test-4.c being sections not listed in the files list.
# -- test4.c and test-5.c being a file not listed in a section.

# The files list should be on a single line.
# Repeated sections do not have to be adjacent.

### test4.h

### file3.h

# That's two of file3.h (not consecutive) - it should be reported as a duplicate.
