#!/bin/bash

join -e 0 -a 1 -a 2 -t $'\t' -o 0,1.2,2.2 \
     <(sed 1d sample001.file | sort) \
     <(sed 1d sample002.file | sort) |
join -e 0 -a 1 -a 2 -t $'\t' -o 0,1.2,1.3,2.2 \
   - <(sed 1d sample003.file | sort)
