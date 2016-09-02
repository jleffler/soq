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

# ----------------------------------------------------------------------

# SO 3929-7530 asked about indirect access to associative arrays.
# http://stackoverflow.com/q/39397530
# User pjh (http://stackoverflow.com/users/4154375/pjh) suggests:

humantocheck=human1

declare -A human1
declare -A human2

human1=( ["records_file"]="xxxxx.txt" )
human2=( ["records_file"]="yyyyy.txt" )

ref="$humantocheck[records_file]"
echo "Records file: ${!ref}"

# pjh complains that the double quotes aren't necessary.
# JL says: I don't like not using them; I plan to continue to use them.

# ----------------------------------------------------------------------

# JL thought of array assigment, but that's painful for associative arrays.
case "$#" in
(0) for key in "${!human1[@]}"; do human[$key]="${human1[$key]}"; done;;
(*) for key in "${!human2[@]}"; do human[$key]="${human2[$key]}"; done;;
esac
echo ${human[records_file]}

# I still see nothing about array assignment in Bash in the docs.
# Clearly, for an non-sparse indexed array, you can use this, but it
# does not work well for associative arrays.

new_array=( "${old_array[@]}" )

# None of this was submitted as a possible answer to the problem; pjh
# got there with a good answer beforehand.

# ----------------------------------------------------------------------

# User Charles Duffy (http://stackoverflow.com/users/14122/charles-duffy)
# suggests:

# This is exactly the scenario that the bash 4.3 feature namevars
# (borrowed from ksh93) is intended to address.  Namevars allow
# assignment, as opposed to lookup alone, and are thus more flexible
# than the ${!foo} syntax.
#
# See BashFAQ #6 (http://mywiki.wooledge.org/BashFAQ/006)

# input
humantocheck="human1"

declare -A human1=( ["records_file"]="xxxxx.txt" )
declare -A human2=( ["records_file"]="yyyyy.txt" )

declare -n human=$humantocheck # make human an alias for, in this case, human1
echo "${human[records_file]}"  # use that alias
unset -n human                 # discard that alias

