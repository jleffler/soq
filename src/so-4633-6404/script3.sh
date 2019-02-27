#!/bin/bash

comm <(sed 's/^/X/' 1.indented.txt) <(sed 's/^/X/' 2.indented.txt) |
sed -f script3.sed
