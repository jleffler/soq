#!/bin/bash
#
# Collect surnames, male and female surnames from https://names.mongabay.com

nbncl <<'EOF' |

# File-name                 URL
# Surnames
us-surnames-00001-01000             https://names.mongabay.com/most_common_surnames.htm
us-surnames-01001-02000             https://names.mongabay.com/most_common_surnames1.htm
us-surnames-02001-05000             https://names.mongabay.com/most_common_surnames2.htm
us-surnames-05001-08000             https://names.mongabay.com/most_common_surnames5.htm
us-surnames-08001-12000             https://names.mongabay.com/most_common_surnames8.htm
us-surnames-12001-16000             https://names.mongabay.com/most_common_surnames12.htm
us-surnames-16001-18839             https://names.mongabay.com/most_common_surnames16.htm

# Male names
us-male-names-0001-0300             https://names.mongabay.com/male_names.htm
us-male-names-0301-0600             https://names.mongabay.com/male_names3.htm
us-male-names-0601-0900             https://names.mongabay.com/male_names6.htm
us-male-names-0901-1219             https://names.mongabay.com/male_names9.htm

# Female names
us-female-names-0001-1000           https://names.mongabay.com/female_names.htm
us-female-names-1001-2000           https://names.mongabay.com/female_names1.htm
us-female-names-2001-3000           https://names.mongabay.com/female_names2.htm
us-female-names-3001-4275           https://names.mongabay.com/female_names3.htm

EOF

while read base url
do
    echo "$base"
    html="$base.html"
    data="$base.data"
    curl -o "$html" "$url"
    extags -t table "$html" | unhtml | column -t > "$data"
done
