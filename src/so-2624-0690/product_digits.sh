for number in "$@"
do
    echo "$number"
done | sed 's/./&*/g; s/$/1/' | bc
