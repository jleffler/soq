#!/bin/bash
#
# Collect top-page scores from Stack Overflow (run by cron)

top_users='https://stackoverflow.com/users?tab=Reputation&filter=all'
dir="$HOME/soq/Scores"
mkdir -p "$dir"
cd "$dir"

time="$(isodate compact)"
raw="raw.$time"

trap "rm -f raw.$time log.$time" 0 1 2 3 13 15

curl -o "$raw" "$top_users"

{
isodate
ule -n -u "$raw" |
sed -n '/<div class="user-details">/,/<.div>/{
            \@href="/users/@ { s@.*="/users/@@; s@</a>.*@@; s@">@ - @; s@/@ - @p; n; }
            /title="reputation score [0-9]*"/ {
                s@.*title="reputation score @@
                s@".*="\([0-9][0-9]* gold\).*="\([0-9][0-9]* silver\).*="\([0-9][0-9]* bronze\).*@ - \1 - \2 - \3@p
                n; }
        }' |
awk 'NR % 2 == 1 { save = $0 } NR % 2 == 0 { print ++rank " - " save " - " $0 }'
} > "top.$time"

