#!/bin/bash
#
# SO 4895-9122

tmp=$(mktemp ./name.XXXXXXX)
trap "rm -f filename.txt $tmp; exit 1" 0 1 2 3 13 15

cat > filename.txt <<'EOF'
"claim":"913-213-2234","claimant":"Percival Meredew","date":"2018-01-30","client":"c62e-c5a9-4611-91c6-118b4ee","address":"2341 Example Lane, Anytown, SS 98765, USA"
EOF

set -x
export "claimant"="absolute nonsense"
echo "[$claimant]"

echo export $(awk -F',' '{sub(/:/, "=", $4); print $4}' filename.txt)
echo export $(awk -F',' '{sub(/:/, "=", $3); print $3}' filename.txt)
echo export $(awk -F',' '{f=$5; sub(/:/, "=", f); print f}' filename.txt)

for n in $(range 1 5)
do
    echo export $(awk -F',' -v n=$n '{f = $n; sub(/:/, "=", f); print f}' filename.txt)
done

export $(echo '"client"="grunge"')
export $(echo 'client="grunge"')
echo "$client"
echo export $(echo 'client="grunge"')
export $(echo '"claimant"="Percival Meredew"')

eval export $(awk -F',' -v n=4 '{f = $n; sub(/:/, "=", f); print f}' filename.txt)

for n in $(range 1 4)
do
    echo export $(awk -F',' -v n=$n '{f = $n; sub(/:/, "=", f); print f}' filename.txt)
done > $tmp

. $tmp

rm -f filename.txt $tmp
trap 0
