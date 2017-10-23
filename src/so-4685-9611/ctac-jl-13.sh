#!/bin/sh
#
# SO 4685-9611
#
# JL revision of ctac13.sh
# https://stackoverflow.com/users/8592975/ctac

# This works mirrors the Perl code in domains83.pl, using arrays s and t
# both indexed by the 3-part domain name.
#awk -F. '
#NF > 3 { d2 = $(NF-1) "." $NF; d3 = $(NF-2) "." d2; s[d3]++; t[d3] = d2 }
#END { for (i in s) if (s[i] >= 4) u[t[i]]++; for (i in u) print i }' "$@"

# This more closely mirrors the code in ctac13.sh by ctac_, using a
# single array indexed by 3-part domain name and editing those to
# generate the second list.  It uses (much) less space, so it is
# potentially more efficient.
awk -F. '
NF > 3 { count[$(NF-2) "." $(NF-1) "." $NF]++ }
END { for (i in count) if (count[i] >= 4) { sub(/^[^.]+\./, "", i); domains[i]++ }
      for (i in domains) print i
    }' "$@"
