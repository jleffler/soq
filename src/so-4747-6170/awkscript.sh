exec ${AWK:-awk} '{s=substr($2,1,3); print >> "split_DB/" s ".part"}' "$@"
