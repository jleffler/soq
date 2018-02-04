#!/bin/sh
#
# Standard comment on reserved identifiers in C

tr -s ' \t\n' '   ' <<'EOF'

Note that you should not create function or variable names that start
with an underscore, in general.
[C11 §7.1.3 Reserved
identifiers](https://port70.net/~nsz/c/c11/n1570.html#7.1.3) says (in
part):

— _All identifiers that begin with an underscore and either an
uppercase letter or another underscore are always reserved for any use._

— _All identifiers that begin with an underscore are always reserved
for use as identifiers with file scope in both the ordinary and tag name
spaces._

See also [What does double underscore (`__const`) mean in
C?](https://stackoverflow.com/a/1449301/15168)

EOF
