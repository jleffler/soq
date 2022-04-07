#!/bin/sh
#
# Standard comment on misusing realloc

tr -s ' \t\n' '   ' <<'EOF'

Note that you should avoid using `realloc()` like this: `old_size =
function_of(old_isze); old_ptr = realloc(old_ptr, old_size);`.  If
`realloc()` fails, you've lost the pointer to the old memory (and the
size of the old block too), so you have a memory leak as well failing to
allocate more space.  Use code like: `size_t new_size =
function_of(old_size); void *new_ptr = realloc(old_ptr, new_size); if
(new_ptr == NULL) { …handle failure… } else { old_size = new_size;
old_ptr = new_ptr; }`.  This keeps control of the old space until you
know the memory reallocation succeeded.

EOF
echo ''
