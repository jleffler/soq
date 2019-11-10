#!/bin/sh
#
# Don't use the esql tag on SO

cat <<'EOF'
Do not use the [tag:esql] tag on SO because it is ambiguous.
Use one of the tags [tag:embedded-sql], [tag:entity-sql] or
[tag:extended-sql], depending on which variant of ESQL you wish
to ask about.
See the [ESQL tag info](https://stackoverflow.com/tags/esql/info)
for more information about which to use if it is not immediately
obvious to you.
It isn't obvious to me from the information in the question which
is the correct tag for you to use.
EOF
