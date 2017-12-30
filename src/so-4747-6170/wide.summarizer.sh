{
echo "Script Variant"
echo "N"
echo "Mean"
echo "Std Dev"
echo "Min"
echo "Max"
echo

grep -hE -e '  -  [0-9]+\.[0-9]+s  -  ' "$@" |
colnum -c 8,11 |
sed 's/\([0-9]\)s/\1/' |
SAMPLE_STATS="-n -mean -sd -min -max -f %.3f" samplestats -k2 -v1 |
sed -e 's/^[^#]/$@&/' \
    -e 's/^# [^=]*= \([0-9][0-9.]*\).*/\1/' \
    -e 's/$/ |/' |
tr -d '\n' |
tr '$' '\n' |
sort -t'|' -k3gr,3 |
sh map-names.sh |
tr '@|' '\n\n'
} |

sh tabulate.sh
