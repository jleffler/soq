#!/bin/sh
#
# @(#)$Id$
#
# Test program ptest.segfaults to destruction

valgrind --log-file=ptest.$(isodate compact).log -- \
        ptest.segfaults bible12.txt begat Abraham Jesus asynonimitousness extravaganza \
        abcedefhijklmnopqrstuvwxyz qqqqqqqqxxqqqqzzqqqqqqjjqqqqqq

