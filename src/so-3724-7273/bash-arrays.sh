#!/bin/bash
# SO 37247273

array1=("A" "B")
array2=("C" "D" "  E  F  ")

#for i in $(seq 1 2)
#do
#    for elm in ${array${i}[@]}
#    do
#        echo "the element in array$i is $elm"
#    done
#done

#-=JL=-
#for i in $(seq -f 'array%.0f[@]' 1 2)
for i in 'array1[@]' 'array2[@]'
do
    for elm in "${!i}"
    do
        echo "the element in $i is [$elm]"
    done
done

#-=JL=-
for i in 'a' 'b'; do echo "$i"; done
for i in 'a[@]' 'b[@]'; do echo "$i"; done

# A.N.Other
for i in $(seq 1 2)
do
    var=array$i[@]
    echo "var=$var"
    for elm in "${!var}"
    do
        echo "the element in $i is [$elm]"
    done
done
