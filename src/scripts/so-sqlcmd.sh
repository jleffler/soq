
#!/bin/sh
#
# Standard spiel about JLSS SQLCMD

cat <<'EOF'

Consider using SQLCMD (available from the [IIUG Software
Archive](https://www.iiug.org/en/iiug-software-repository/#ESQL)), which
I wrote to behave consistently in shell scripting contexts whereas
DB-Access doesn't.
It dates back to 1986 (before there was `dbaccess`; in those days, you
used `isql` instead — DB-Access was carved out of `isql` in an
evening).
It bears no relation to Microsoft's johnny-come-lately program of the
same name — except for the name and having the same general purpose
(manipulate SQL databases).

EOF
