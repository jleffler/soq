#!/bin/sh
#
# Check the results from running a test
# Clearly, this is extremely simplistic; it does give reassurance that
# there isn't twice as much data as intended, or no data.

ls split_DB | wc -l
wc split_DB/* | tail -n 2
