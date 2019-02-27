#!/bin/sh
#
# Run a big test with 1,000,000 rows by default

sh test-setup.sh

time (timecmd -msr -- sh data.generator.sh ${1:-1000000} |
      timecmd -msr -- sort -k2,2 |
      timecmd -msr -- perl jlperl-4.pl)

sh test-check.sh
