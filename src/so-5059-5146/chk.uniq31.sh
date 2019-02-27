rmk uniq31 || exit

echo          | uniq31
echo 11       | uniq31
echo 10 10    | uniq31
echo 10 11    | uniq31
echo 10 10 10 | uniq31
echo 10 10 11 | uniq31
echo 10 11 11 | uniq31
echo 10 11 12 | uniq31

random -n  18  10  30 | uniq31
random -n  18  10  50 | uniq31
random -n  18  10  90 | uniq31
random -n  20  10  30 | uniq31
random -n  30  10  30 | uniq31
random -n  54  10  30 | uniq31
random -n  72  10  30 | uniq31
random -n 100 100 300 | uniq31

for triple in \
    "  18  10  30" \
    "  18  10  50" \
    "  18  10  90" \
    "  20  10  30" \
    "  30  10  30" \
    "  54  10  30" \
    "  72  10  30" \
    " 100 100 300"
do
    random -n $triple |
    tee data.$$ |
    uniq31 |
    tee result.$$
    sort -un data.$$ | tee sort.1.$$ | wc
    sed -n '/Unique/,${ /Unique/d; p; }' result.$$ |
    tr -s ' ,' '\n' |
    sort -un | tee sort.2.$$ | wc
    diff sort.[12].$$
    rm -f data.$$ result.$$ sort.1.$$ sort.2.$$
done
