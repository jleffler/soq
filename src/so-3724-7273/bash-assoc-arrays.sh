declare -A aa
aa+=( [a1]="large size paper" )
aa+=( ["a2"]="medium-large size paper" )
aa+=( [a0]="biggest size paper" )
aa+=( ["a 6"]="rather small paper" )
echo "aa contains ${#aa[@]} elements (\${#aa[@]})"
echo "-- Values (\${aa[@]})"
al "${aa[@]}"
echo "-- Keys (\${!aa[@]})"
al "${!aa[@]}"
echo "-- Keys (\${!aa[*]})"
al ${!aa[*]}
echo "-- Rows"
for tag in "${!aa[@]}"
do echo "$tag = ${aa[$tag]}"
done
unset aa
