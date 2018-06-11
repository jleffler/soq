#!/bin/sh
#
# Collect US Zipcode data by state
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
    curl -s -S -o "us-zipcodes-$state.html" "https://data.mongabay.com/igapo/zip_codes/$state.htm"
done
