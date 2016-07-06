#!/bin/sh
#
# Check that there is a reference in $1 to each of the other arguments.

status=0
source=$1
shift

for file in "$@"
do
	if grep -q "^### $file$" ${source}
	then : OK
	else echo "$file - not referenced" >&2
		 status=1
	fi
done

exit $status
