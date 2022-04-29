#!/bin/sh
#
# Standard commentary on using realloc


tr -s ' \t\n' '   ' <<'EOF'

Note that the idiom `old_ptr = realloc(old_ptr, new_size);` risks
leaking the previous memory if the reallocation fails.
Use `size_t new_size = old_size * 2;` (or any other function of the old
size), `void *new_ptr = realloc(old_ptr, new_size); if (new_ptr == NULL)
{ …deal with no memory available… } old_ptr = new_ptr; old_size =
new_size;` or minor variants on the theme.

EOF
echo ''
