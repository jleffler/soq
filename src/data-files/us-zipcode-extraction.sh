#!/bin/sh
#
# Extract US Zipcode data by state
# Zip Codes by US State — AL: https://data.mongabay.com/igapo/zip_codes/AL.htm

for state in \
        AK  AL  AR  AZ  CA  CO  CT  DC  DE  FL \
        GA  HI  IA  ID  IL  IN  KS  KY  LA  MA \
        MD  ME  MI  MN  MO  MS  MT  NC  ND  NE \
        NH  NJ  NM  NV  NY  OH  OK  OR  PA  PR \
        RI  SC  SD  TN  TX  UT  VA  VT  WA  WI \
        WV  WY
do
    echo "$state"
    base="us-zipcodes-$state"
    html="$base.html"
    data="$base.data"
    if [ -s "$html" ]
    then
        # grep | sed should be replaced by sed-only!
        grep -o -E -e '^[0-9]{5}[[:space:]]+[[:alpha:][:space:]]+\([0-9]{3}\)' "$html" |
        sed -e 's/^\([0-9]\{5\}\)  */'"$state"'|\1|/' \
            -e 's/  *(\([0-9]\{3\}\))/|\1/' |
        sort -t'|' -k2,2 -k3,3 > "$data"
    else echo "No file $html for state $state" >&2
    fi
done
